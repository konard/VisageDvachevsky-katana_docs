# Stage 3 — Runtime Hardening + Contract Surface: План реализации

## Summary стратегии

Stage 3 решает пять задач: media type registry, conformance harness, стабилизация test path, ревизия x-katana-* extensions, синхронизация docs. Задачи имеют чёткую зависимость: **media type registry → conformance harness → docs sync**, при этом **test path stabilization** и **x-katana-* ревизия** могут идти параллельно основному потоку.

Стратегия — **bottom-up**: сначала вводим абстракцию `media_type_registry` (единую точку правды для форматов), затем подключаем её в codegen и runtime, после чего строим conformance harness поверх уже стабильного API. Финальный день — docs sync и closeout checklist.

---

## Assumptions

1. **Один инженер** с хорошим знанием C++23, CMake, кодовой базы KATANA.
2. **Linux** — основная dev-платформа; WSL-совместимость проверяется, но не блокирует.
3. **Нет внешних зависимостей** в Stage 1-3 — CBOR/MessagePack реализуются как стабовые serializers (header-only), реальные кодеки могут быть подключены позже. Цель Stage 3 — registry/negotiation, а не production-ready CBOR.
4. **Codebase зелёная** — текущие тесты проходят на debug preset. Если нет — починка входит в Day 1.
5. **katana_gen** уже генерирует content negotiation bindings для JSON — расширение на новые media types через registry.
6. **x-katana-* extensions** парсятся в `openapi_loader.cpp` (строки 1239-1265) и сохраняются в `operation::x_katana_cache`, `x_katana_alloc`, `x_katana_rate_limit`; runtime их пока не интерпретирует.
7. **gtest-совместимый** лёгкий harness (`test/gtest/gtest.h`) — все новые тесты используют его, GoogleTest не нужен.

---

## Aggressive Plan (5-7 рабочих дней)

### Day 1 — Baseline + media_type_registry core

**Цель дня**: зафиксировать green baseline, спроектировать и реализовать ядро media type registry.

**Задачи**:

1. **Green baseline** — собрать и прогнать тесты:
   ```bash
   cmake --preset debug && cmake --build --preset debug && ctest --preset debug
   ```
   Если что-то красное — починить до продолжения.

2. **Design decision: API `media_type_registry`** — определить контракт:
   ```cpp
   // katana/core/include/katana/core/media_type_registry.hpp
   namespace katana::http {

   enum class media_format : uint8_t { json, cbor, msgpack };

   struct media_type_entry {
       std::string_view mime;         // "application/json"
       media_format format;           // media_format::json
       // serialize: DTO → bytes; deserialize: bytes → DTO
       // На Stage 3 — стабы для cbor/msgpack, реальный только json
   };

   class media_type_registry {
   public:
       void register_type(media_type_entry entry);
       const media_type_entry* find(std::string_view mime) const noexcept;
       const media_type_entry* negotiate(std::string_view accept_header) const noexcept;
       std::span<const media_type_entry> all() const noexcept;
       static media_type_registry& default_instance(); // JSON pre-registered
   };

   } // namespace katana::http
   ```

3. **Реализация** `media_type_registry.hpp` (header-only или .hpp + .cpp):
   - `register_type()` — добавляет запись (максимум 8-16 записей, линейный поиск достаточен).
   - `find()` — exact match по MIME строке.
   - `negotiate()` — выбор лучшего типа из Accept header (q-value aware, расширение текущей `validate_accept()`).
   - `default_instance()` — singleton с `application/json` зарегистрированным по умолчанию.

4. **Unit тесты** `test/unit/test_media_type_registry.cpp`:
   - Регистрация JSON/CBOR/MessagePack.
   - `find()` по точному MIME.
   - `negotiate()` с q-values: `application/cbor;q=1.0, application/json;q=0.9`.
   - `negotiate()` с wildcard `*/*`.
   - Пустой Accept → JSON по умолчанию.

**Затрагиваемые файлы**:
- **Новый**: `katana/core/include/katana/core/media_type_registry.hpp`
- **Новый**: `katana/core/src/media_type_registry.cpp` (если не header-only)
- **Новый**: `test/unit/test_media_type_registry.cpp`
- **Изменения**: `katana/core/CMakeLists.txt` (добавить .cpp и тест)

**Результат к концу дня**: `media_type_registry` собирается, тесты проходят, JSON/CBOR/MessagePack зарегистрированы (CBOR и MessagePack — стабы).

**Проверка**: `ctest --preset debug -R test_media_type_registry` — зелёный.

**Риски**: если текущий baseline красный, починка может занять полдня. Митигация: параллельно читать код content_negotiation.hpp и планировать интеграцию.

---

### Day 2 — Интеграция registry в runtime + stub serializers

**Цель дня**: подключить registry к content negotiation middleware и HTTP server; создать стаб-сериализаторы для CBOR/MessagePack.

**Задачи**:

1. **Stub serializers**:
   ```cpp
   // katana/core/include/katana/core/media_serializers.hpp
   namespace katana::serde {

   // JSON — уже есть (serde.hpp, json_parser.hpp)
   // CBOR stub — возвращает ошибку "not implemented" или минимальный envelope
   // MessagePack stub — аналогично
   struct serializer {
       using serialize_fn = std::string(*)(std::string_view json_body);
       using deserialize_fn = std::string(*)(std::string_view raw_body);
       serialize_fn serialize;
       deserialize_fn deserialize;
   };

   const serializer& json_serializer();
   const serializer& cbor_serializer();     // stub
   const serializer& msgpack_serializer();  // stub

   } // namespace katana::serde
   ```

2. **Рефакторинг `content_negotiation.hpp`**:
   - Заменить `std::span<const content_type_info>` на ссылку на `media_type_registry` (или оставить span, но заполнять его из registry).
   - `make_content_negotiation_middleware()` принимает `const media_type_registry&` вместо двух span.
   - Сохранить обратную совместимость: старая сигнатура остаётся как overload (deprecated).

3. **Интеграция в HTTP server** (`http_server.cpp`):
   - По умолчанию использовать `media_type_registry::default_instance()`.
   - При получении запроса с `Accept: application/cbor` и зарегистрированным CBOR — попытка сериализации через stub (который вернёт 501 Not Implemented или заглушку).

4. **Тесты**:
   - `test/unit/test_content_negotiation.cpp` (расширить существующие в `test_http.cpp` или отдельный файл):
     - Запрос `Accept: application/cbor` → корректный ответ (stub serializer).
     - Запрос `Accept: application/xml` (не зарегистрирован) → 406.
     - Запрос `Content-Type: application/msgpack` → 415 если не в consumes.

**Затрагиваемые файлы**:
- **Новый**: `katana/core/include/katana/core/media_serializers.hpp`
- **Новый**: `katana/core/src/media_serializers.cpp`
- **Изменения**: `katana/core/include/katana/core/content_negotiation.hpp`
- **Изменения**: `katana/core/src/http_server.cpp` (опционально)
- **Изменения/Новый**: `test/unit/test_content_negotiation.cpp`
- **Изменения**: `katana/core/CMakeLists.txt`

**Результат**: runtime понимает JSON/CBOR/MessagePack через registry; CBOR/MsgPack — стабы, JSON — полнофункционален.

**Проверка**: `ctest --preset debug` — все существующие тесты зелёные + новые тесты.

**Риски**: изменение сигнатуры `make_content_negotiation_middleware()` может сломать codegen bindings. Митигация: добавить перегрузку, не убирать старую.

---

### Day 3 — Интеграция registry в codegen + x-katana-* ревизия

**Цель дня**: katana_gen генерирует bindings с поддержкой media type registry; провести ревизию x-katana-* extensions.

**Задачи**:

1. **Codegen: `router_generator.cpp`** — сгенерированные bindings должны:
   - Использовать `media_type_registry` для определения доступных форматов вместо хардкода `"application/json"`.
   - При наличии нескольких media types в OpenAPI spec `content:` — генерировать switch по `media_format` для выбора serializer.
   - Пример: если операция `produces: [application/json, application/cbor]`, binding вызывает `registry.negotiate(accept_header)` и сериализует через соответствующий serializer.

2. **Codegen: `json_generator.cpp`** — убедиться, что сгенерированные парсеры/сериализаторы регистрируются как JSON serializer в registry (или могут быть вызваны из generic serializer interface).

3. **x-katana-* ревизия** — создать документ `docs/X_KATANA_EXTENSIONS.md`:
   - **x-katana-cache**: парсится, хранится в AST. Runtime интерпретация — Stage 5 (Redis). Статус: **декларативный, без runtime-эффекта в Stage 3**.
   - **x-katana-alloc**: парсится, хранится в AST. Может влиять на выбор аллокатора в codegen (pmr vs std). Статус: **частично поддержан codegen** (через `--alloc` CLI flag), per-operation override — не реализован.
   - **x-katana-rate-limit**: парсится, хранится в AST. Runtime middleware — Stage 5+. Статус: **декларативный, без runtime-эффекта в Stage 3**.
   - Для каждого extension: описать формат, валидацию, пример, текущий статус поддержки (parsed / codegen / runtime).
   - **Design decision**: вводить ли новые extensions на Stage 3? Рекомендация: нет. Зафиксировать контракт текущих трёх, не расширять до Stage 5.

4. **Тесты codegen**:
   - Расширить `test/unit/test_codegen_integration.cpp`: OpenAPI fixture с `content: { application/json: ..., application/cbor: ... }` → сгенерированный binding корректно обрабатывает оба формата.
   - Snapshot-тест: сгенерированный код для multi-media operation совпадает с expected output.

**Затрагиваемые файлы**:
- **Изменения**: `tools/katana_gen/router_generator.cpp`
- **Изменения**: `tools/katana_gen/generator_utils.cpp` (если нужны helper-функции)
- **Новый**: `docs/X_KATANA_EXTENSIONS.md`
- **Изменения**: `test/unit/test_codegen_integration.cpp`
- Опционально: `test/unit/test_codegen_snapshots.cpp`

**Результат**: codegen генерирует registry-aware bindings; x-katana-* контракт задокументирован.

**Проверка**: `ctest --preset debug` зелёный; `katana_gen openapi -i <fixture> -o /tmp/gen --emit all` без ошибок; `docs/X_KATANA_EXTENSIONS.md` существует.

**Риски**: сложность multi-media codegen может быть выше ожидаемой. Митигация: на Day 3 достаточно генерировать `if/else` по MIME, оптимизация — позже.

---

### Day 4 — Conformance harness + test path stabilization

**Цель дня**: создать conformance test suite для сгенерированных endpoints; стабилизировать test path для Linux/WSL.

**Задачи**:

1. **Conformance harness** — `test/conformance/` directory:
   - **OpenAPI fixture**: `test/conformance/fixtures/petstore_minimal.json` — минимальный OpenAPI spec с CRUD operations, multiple media types, параметрами всех типов (path, query, header, cookie).
   - **Сгенерированный код**: `test/conformance/generated/` — результат `katana_gen` по fixture.
   - **Conformance tests** `test/conformance/test_conformance.cpp`:
     - Для каждой операции в fixture: создать request → dispatch через generated router → проверить status code, Content-Type, body format.
     - Проверки:
       - Корректный routing (GET /pets/{id} → getById handler).
       - Content negotiation: `Accept: application/json` → JSON, `Accept: application/cbor` → CBOR stub или 406.
       - Validation: невалидный body → 400 с Problem Details.
       - 404/405 для несуществующих/запрещённых путей.
       - Path/query/header parameter extraction.
     - Использовать `test/support/http_handler_harness.hpp` для тестирования без реактора.

2. **CMake интеграция**:
   - Добавить custom command для генерации кода из fixture перед сборкой тестов.
   - Или pre-commit сгенерированные файлы (проще для CI).

3. **Test path stabilization**:
   - Проверить, что все presets (`debug`, `release`, `asan`, `tsan`, `ubsan`) собираются и проходят на Linux.
   - Проверить WSL-совместимость: `cmake --preset debug` под WSL → build → test.
   - Зафиксировать любые platform-specific проблемы (paths, line endings, sched_setaffinity на WSL).
   - Добавить в `CMakePresets.json` секцию `"condition"` для io_uring presets (доступен только на Linux kernel ≥ 5.10).
   - Убедиться, что `ctest --preset debug` выполняет все тесты включая новые conformance.

4. **Perf smoke test**:
   - Добавить простой perf smoke в `test/integration/test_perf_smoke.cpp`:
     - Запустить HTTP server, послать 1000 запросов, проверить что p99 < 5ms (на любом dev-оборудовании).
     - Не benchmark (тот уже есть), а **gate**: если p99 > порога — fail.
   - Подключить к `ctest --preset debug` или отдельный preset.

**Затрагиваемые файлы**:
- **Новый**: `test/conformance/` directory
- **Новый**: `test/conformance/fixtures/petstore_minimal.json`
- **Новый**: `test/conformance/generated/` (сгенерированный код)
- **Новый**: `test/conformance/test_conformance.cpp`
- **Новый**: `test/integration/test_perf_smoke.cpp` (опционально)
- **Изменения**: `CMakeLists.txt` (или `test/CMakeLists.txt`)
- **Изменения**: `CMakePresets.json` (если нужны condition для io_uring)

**Результат**: conformance suite работает и зелёный; тесты запускаются одинаково на Linux и WSL; perf smoke не регрессирует.

**Проверка**: `ctest --preset debug -R conformance` зелёный; `ctest --preset debug` зелёный; `ctest --preset asan` зелёный.

**Риски**: WSL может не поддерживать `sched_setaffinity` или io_uring. Митигация: тесты, зависящие от этих API, должны быть обёрнуты в runtime-check (уже реализовано для reactor).

---

### Day 5 — Docs sync + polish + Stage 3 closeout

**Цель дня**: привести README и docs в соответствие с фактическим состоянием; финальный прогон; закрытие Stage 3.

**Задачи**:

1. **README.md sync**:
   - Секция «Текущее состояние»: добавить ✅ для media type registry, conformance harness.
   - Секция «В разработке»: убрать `⏳ Media type registry (CBOR/MessagePack) — отнесено в Stage 3`.
   - Этап 3: пометить как **завершён** с кратким описанием закрытых пунктов.
   - Убрать или пометить целевые описания, которые ещё не реализованы (SQL, Redis, etc.) — сохранить маркер «планируется».

2. **ARCHITECTURE.md sync**:
   - Обновить status caveat (строка 29-35): отразить новый media type registry.
   - Если какие-то описания архитектуры не соответствуют реальности — пометить явно.

3. **docs/OPENAPI.md sync**:
   - Добавить секцию «Media Type Registry» — описание API, supported formats.
   - Обновить секцию кодогенерации: упомянуть multi-media bindings.

4. **docs/X_KATANA_EXTENSIONS.md** — финальная редактура (создан на Day 3).

5. **CONTRIBUTING.md** — добавить секцию про conformance tests, если нужно.

6. **Full CI prогон**:
   ```bash
   cmake --preset debug && cmake --build --preset debug && ctest --preset debug
   cmake --preset asan && cmake --build --preset asan && ctest --preset asan
   cmake --preset ubsan && cmake --build --preset ubsan && ctest --preset ubsan
   ```

7. **Stage 3 closeout checklist** (см. ниже).

**Затрагиваемые файлы**:
- **Изменения**: `README.md`
- **Изменения**: `ARCHITECTURE.md`
- **Изменения**: `docs/OPENAPI.md`
- **Изменения**: `docs/X_KATANA_EXTENSIONS.md`
- **Изменения**: `CONTRIBUTING.md` (минимально)

**Результат**: документация отражает фактическое состояние; все тесты зелёные; Stage 3 закрыт.

**Проверка**: `grep -r "Stage 3" README.md` показывает завершённый статус; `ctest --preset debug` зелёный; `ctest --preset asan` зелёный.

---

## Safer Plan (8-12 рабочих дней)

### Day 1-2 — Baseline + Design

**Day 1**: зафиксировать green baseline, исследовать codebase (content_negotiation.hpp, serde.hpp, router_generator.cpp), зафиксировать design decisions в ADR-файле.

**Day 2**: реализовать `media_type_registry` core + unit тесты. Без интеграции в runtime.

### Day 3-4 — Stub serializers + runtime интеграция

**Day 3**: реализовать stub serializers для CBOR/MessagePack, интерфейс `serializer`.

**Day 4**: интегрировать registry в `content_negotiation.hpp` и HTTP server. Тесты content negotiation с registry.

### Day 5-6 — Codegen интеграция

**Day 5**: модифицировать `router_generator.cpp` для генерации registry-aware bindings. Тесты codegen.

**Day 6**: snapshot-тесты, edge cases (операция без media types, операция с одним media type, wildcard Accept). Починить регрессии если есть.

### Day 7 — x-katana-* ревизия

Создать `docs/X_KATANA_EXTENSIONS.md`. Проверить корректность парсинга всех трёх extensions. Добавить тесты для edge cases парсинга (пустые значения, невалидные форматы).

### Day 8-9 — Conformance harness

**Day 8**: создать OpenAPI fixture, сгенерировать код, скелет conformance тестов.

**Day 9**: полный набор conformance тестов (routing, negotiation, validation, error responses).

### Day 10 — Test path stabilization

Проверить все presets на Linux. Проверить WSL. Добавить perf smoke. Починить platform-specific проблемы.

### Day 11 — Docs sync

README, ARCHITECTURE, OPENAPI, X_KATANA_EXTENSIONS, CONTRIBUTING.

### Day 12 — Stage 3 closeout

Полный CI прогон (debug, asan, tsan, ubsan). Финальный review. Закрытие Stage 3.

---

## Critical Path

```
[Day 1] media_type_registry core
    ↓
[Day 2] runtime интеграция (content_negotiation + stub serializers)
    ↓
[Day 3] codegen интеграция (router_generator)
    ↓
[Day 4] conformance harness (зависит от registry + codegen)
    ↓
[Day 5] docs sync + closeout
```

**Длина critical path: 5 дней** (aggressive) / **12 дней** (safer).

**Параллельные потоки** (могут идти одновременно с critical path):
- x-katana-* ревизия (Day 3 aggressive / Day 7 safer) — не блокирует и не блокируется другими задачами.
- Test path stabilization (Day 4 aggressive / Day 10 safer) — может начаться после Day 1 baseline.
- Perf smoke (Day 4 aggressive / Day 10 safer) — зависит только от baseline.

---

## Design Decisions (нужны до начала кодинга)

1. **Registry API: статический vs dynamic** — рекомендация: static (pre-populated at startup), без runtime add/remove. Проще, достаточно для Stage 3.

2. **Serializer interface: function pointers vs virtual** — рекомендация: function pointers (zero overhead, header-only). Virtual — overkill для 3-5 форматов.

3. **q-value negotiation: полный RFC 7231 vs simplified** — рекомендация: simplified (парсить q-values, выбирать max q, ties — порядок в registry). Полный RFC 7231 (level parameters, charset) — Stage 7+.

4. **CBOR/MessagePack stubs: 501 Not Implemented vs minimal encoding** — рекомендация: 501 Not Implemented с Problem Details body. Это честнее и проще тестировать. Минимальный encoding (header-only CBOR/MsgPack) можно добавить позже.

5. **Conformance fixtures: предкоммиченные generated файлы vs CMake custom command** — рекомендация: предкоммиченные файлы. Проще для CI, не требует рабочего katana_gen для запуска тестов. Регенерация — ручная при изменении fixture.

6. **content_negotiation.hpp: breaking change vs deprecation** — рекомендация: добавить новый overload `make_content_negotiation_middleware(const media_type_registry&)`, старый оставить как deprecated. Удалить старый в Stage 4.

---

## Rollback / Minimum-Scope Option

Если придётся резать объём, **минимальный usable scope**:

### Must-have (3 дня):
1. `media_type_registry` с JSON + stubs для CBOR/MsgPack.
2. Интеграция registry в `content_negotiation.hpp` (новый overload).
3. Unit тесты registry + content negotiation.
4. `docs/X_KATANA_EXTENSIONS.md` с текущим статусом.

### Nice-to-have (оставшиеся дни):
5. Codegen интеграция (multi-media bindings).
6. Conformance harness.
7. Test path stabilization (presets, WSL).
8. Полный docs sync.
9. Perf smoke test.

### Можно отложить без ущерба:
- Perf smoke gate (уже есть benchmark harness).
- WSL-specific fixes (если Linux CI зелёный).
- Полный RFC 7231 q-value negotiation.

---

## Final Stage 3 Closure Checklist

### Код
- [ ] `media_type_registry.hpp` реализован, unit-тесты зелёные
- [ ] JSON/CBOR/MessagePack зарегистрированы в registry (CBOR/MsgPack — stubs)
- [ ] `content_negotiation.hpp` использует registry (новый overload)
- [ ] Stub serializers возвращают 501 для CBOR/MsgPack
- [ ] `router_generator.cpp` генерирует registry-aware bindings
- [ ] Обратная совместимость: старый API content_negotiation не сломан

### Тесты
- [ ] `test/unit/test_media_type_registry.cpp` — зелёный
- [ ] `test/unit/test_content_negotiation.cpp` — зелёный (registry-aware тесты)
- [ ] `test/unit/test_codegen_integration.cpp` — расширен multi-media тестами, зелёный
- [ ] `test/conformance/test_conformance.cpp` — зелёный (routing, negotiation, validation, errors)
- [ ] Все существующие тесты не сломаны: `ctest --preset debug` полностью зелёный

### CI / Sanitizers
- [ ] `ctest --preset debug` — зелёный
- [ ] `ctest --preset asan` — зелёный (если preset доступен)
- [ ] `ctest --preset ubsan` — зелёный (если preset доступен)
- [ ] Одинаковый результат на Linux и WSL (если WSL доступен)

### x-katana-* Extensions
- [ ] `docs/X_KATANA_EXTENSIONS.md` описывает все три extensions
- [ ] Для каждого: формат, валидация, пример, статус (parsed / codegen / runtime)
- [ ] Нет новых extensions в Stage 3

### Документация
- [ ] `README.md` — «Текущее состояние» отражает реальность
- [ ] `README.md` — Этап 3 помечен как завершён
- [ ] `ARCHITECTURE.md` — status caveat обновлён
- [ ] `docs/OPENAPI.md` — добавлена секция Media Type Registry
- [ ] `docs/X_KATANA_EXTENSIONS.md` — создан и актуален
- [ ] Нет секций, описывающих нереализованную функциональность без пометки «планируется»

### Conformance
- [ ] OpenAPI fixture существует и покрывает: CRUD, multiple media types, all parameter types
- [ ] Сгенерированный код из fixture — предкоммичен и актуален
- [ ] Conformance тесты проверяют routing, content negotiation, validation, error responses
- [ ] Conformance тесты используют `http_handler_harness.hpp` (без реактора)

### Closeout
- [ ] Все задачи из DoD Stage 3 (README.md строки 647-651) закрыты
- [ ] git log чистый, все изменения закоммичены
- [ ] PR description описывает все изменения
- [ ] Нет TODO/FIXME без привязки к Issue

---

## Объединённые потоки работ

Задачи «media type registry» и «content negotiation refactor» логически являются одним потоком: registry — это data model, content negotiation — это runtime consumer. Разделять их на отдельные workstreams нет смысла, они реализуются последовательно в Days 1-2.

Задачи «x-katana-* ревизия» и «docs sync» можно объединить в один поток «documentation & contract», так как ревизия extensions — это в основном документирование текущего состояния, а не кодирование. В aggressive plan они распределены по Days 3 и 5, в safer plan — Days 7 и 11.

Задачи «conformance harness» и «test path stabilization» тесно связаны: conformance тесты — это часть test path, и стабилизация presets должна учитывать новые тесты. В aggressive plan они оба на Day 4, в safer plan — Days 8-10.
