# Stage 3: Стабилизация test path и canonical Linux/WSL сценария

## 1. Current State Inventory

### Entry Points (build / test / bench)

| Действие | Makefile | CMake Preset | CI workflow | Документация |
|---|---|---|---|---|
| **Build (debug)** | `make build PRESET=debug` | `cmake --preset debug && cmake --build --preset debug` | `ci.yml` / `pr-ci.yml` (ручная cmake -B build …) | README §54, CONTRIBUTING §9 |
| **Unit/integration tests** | `make test PRESET=debug` | `ctest --preset debug` | `ci.yml` job `build-and-test` | README §59, CONTRIBUTING §13 |
| **Sanitizers** | `make test PRESET=asan\|tsan\|ubsan` | `ctest --preset asan\|tsan\|ubsan` | `ci.yml` матрица, `pr-ci.yml` quick-test | CONTRIBUTING §10 |
| **Bench build** | `make bench` (preset `bench`) | `cmake --preset bench && cmake --build --preset bench` | `perf-regression.yml` (cmake -B build, NO preset) | README §61, docs/BENCHMARKING.md §29–32 |
| **Perf smoke (stage 1+2)** | — нет | — нет | `perf-regression.yml` → `tools/katana_bench.py` | docs/BENCHMARKING.md (частично) |
| **Full bench report** | `make bench-report` → `run_benchmarks.sh` → legacy `generate_benchmark_report.py` | — | `manual-benchmarks.yml` | docs/BENCHMARKING_METHODOLOGY.md |
| **Unified runner** | — нет make target | `scripts/run_benchmarks.py` | — не используется в CI | docs/BENCHMARKING.md (source of truth) |
| **Codegen conformance** | — нет | `ctest` запускает `test_codegen_snapshots`, `test_codegen_integration` | `ci.yml` (часть общего ctest) | — нет отдельной документации |
| **Fuzzing** | `make fuzz` | `cmake --preset fuzz && …` | `ci.yml` / `pr-ci.yml` job `fuzzing` | CONTRIBUTING §14 |
| **Docker bench** | `make docker-bench` | — | — нет | Makefile help |
| **Profiling** | `make profile` | — | — нет | docs/profiling/README.md |

### Runners summary

| Runner | Расположение | Стадии | Статус |
|---|---|---|---|
| `tools/katana_bench.py` | `tools/` | Stage 1, 2 (micro) | **Активен в CI** (perf-regression.yml) |
| `scripts/run_benchmarks.py` | `scripts/` | Stages 1–12 (micro + wrk E2E) | **Заявлен как source of truth** в docs/BENCHMARKING.md, но **не используется в CI** |
| `generate_benchmark_report.py` | repo root | legacy full report | **Legacy**, используется в `run_benchmarks.sh` и Docker entrypoint |
| `run_benchmarks.sh` | repo root | wrk-only | Legacy shell wrapper |
| `benchmark.sh` | repo root | legacy cmake + report | Legacy shell wrapper |

---

## 2. Concrete Inconsistencies

### 2.1. Два параллельных benchmark runner'а

- `scripts/run_benchmarks.py` объявлен «maintained source of truth» в docs/BENCHMARKING.md (строка 43).
- CI (`perf-regression.yml`) использует `tools/katana_bench.py` — отдельный скрипт с собственным парсингом и stage-определениями.
- `run_benchmarks.sh` → `generate_benchmark_report.py` — третий, legacy pipeline (используется в `make bench-report` и Docker entrypoint).

**Проблема**: три разных runner'а с разными stage-определениями, разными парсерами вывода и разными наборами бинарников. Результаты несравнимы.

### 2.2. Makefile `bench-report` вызывает legacy runner

```makefile
bench-report:
    ./run_benchmarks.sh        # → generate_benchmark_report.py (legacy)
```

docs/BENCHMARKING.md §43 говорит использовать `scripts/run_benchmarks.py`. Расхождение.

### 2.3. CI build path ≠ local preset path

| Контекст | Build dir | Benchmark binary path |
|---|---|---|
| `cmake --preset bench` (local) | `build/bench/` | `build/bench/benchmark/performance_benchmark` |
| `perf-regression.yml` (CI) | `build/` (cmake -B build) | `build/benchmark/performance_benchmark` |

`tools/katana_bench.py` find_build_dir() ищет `build/benchmark` первым — совпадает с CI. Для локальной сборки через preset `bench` работает только fallback `build/*/benchmark` glob. Сообщение об ошибке подсказывает `cmake --preset debug`, а не `bench`.

### 2.4. Нет test preset для `bench`

`CMakePresets.json` определяет `testPresets` для `debug`, `release`, `asan`, `tsan`, `ubsan` — но **не для `bench`**. Это значит `ctest --preset bench` не работает, хотя `bench` preset включает `ENABLE_TESTING=ON` (наследует от `base`).

### 2.5. README ссылается на несуществующий `docs/TESTING.md`

README.md строка 249: «Дополнительно: гайды в `CONTRIBUTING.md` и `docs/TESTING.md`.» Файл `docs/TESTING.md` не существует.

### 2.6. Нет единого perf smoke target

- `make bench` запускает только `performance_benchmark` (один бинарник).
- Нет make target для «быстрый perf smoke stage 1+2» (то, что CI делает через `tools/katana_bench.py --stage all`).

### 2.7. Stage numbering расхождение

- `scripts/run_benchmarks.py`: 12 стадий (1–8 micro, 9–12 wrk E2E).
- `tools/katana_bench.py`: 2 стадии (1 Core Runtime, 2 Codegen Quality).
- `benchmark/CMakeLists.txt` targets: `bench_stage1`, `bench_stage2`, `bench_all`.
- docs/BENCHMARKING.md: описывает стадии 1–12 со ссылкой на `scripts/run_benchmarks.py`.

### 2.8. `benchmark.sh` build path несовместим с presets

`benchmark.sh` делает `cmake -DCMAKE_BUILD_TYPE=Release … ..` из `build/` — не использует presets, не передаёт Ninja generator. Конфликтует с preset-based workflow.

---

## 3. Target Command Matrix

### Developer (local, Linux/WSL)

| Шаг | Canonical command | Что проверяется | Mandatory / Optional |
|---|---|---|---|
| **Build** | `make build PRESET=debug` | Компиляция (debug, все предупреждения, -Werror) | **Mandatory** |
| **Unit tests** | `make test PRESET=debug` | Unit + integration тесты | **Mandatory** |
| **Lint** | `make lint` | clang-format, cmake-format, pre-commit hooks | **Mandatory** (перед PR) |
| **Sanitizers** | `make test PRESET=asan` | AddressSanitizer | **Mandatory** (для изменений в core) |
| | `make test PRESET=ubsan` | UndefinedBehaviorSanitizer | Recommended |
| | `make test PRESET=tsan` | ThreadSanitizer | Optional (clang-only) |
| **Codegen conformance** | `make test PRESET=debug` (включает snapshot/integration tests) | katana_gen output stability | **Mandatory** (для изменений в codegen) |
| **Perf smoke** | `make perf-smoke` *(NEW)* | Stage 1+2 micro benchmarks (no regressions vs baseline) | **Recommended** (для изменений в core/codegen) |
| **Full bench** | `make bench` | Release build + performance_benchmark | Optional |
| **Full bench report** | `make bench-report` *(UPDATED)* | All stages via unified runner | Optional |
| **Fuzzing** | `make fuzz` | HTTP parser fuzz (60s) | Optional |
| **Profiling** | `make profile` | simple_benchmark с perf | Optional |

### CI

| Trigger | Workflow | What runs | Gate |
|---|---|---|---|
| **PR → main/develop** | `pr-ci.yml` | quick-test matrix + fuzz + lint + static-analysis | Must pass |
| **PR (core/codegen changes)** | `perf-regression.yml` | Stage 1+2 bench → baseline compare | Warn on regression |
| **Push → main/develop** | `ci.yml` | Full matrix (OS × compiler × sanitizer) + fuzz + lint | Must pass |
| **Push → main/develop** | `coverage.yml` | Coverage report → Codecov | Informational |
| **Schedule / manual** | `manual-benchmarks.yml` | Extended benchmarks | Informational |
| **Schedule** | `benchmarks.yml` | Sync BENCHMARK_RESULTS.md → README | Informational |

---

## 4. Recommended Preset Strategy

### Существующие presets — оставить без изменений

Все текущие presets (`debug`, `release`, `asan`, `tsan`, `ubsan`, `fuzz`, `bench`, `examples`, `io_uring-*`) корректны и покрывают нужды.

### Добавить

1. **Test preset `bench`** — позволит запускать `ctest --preset bench` для тестов в Release-конфигурации с бенчмарками:

```json
{
  "name": "bench",
  "configurePreset": "bench",
  "output": { "shortProgress": true }
}
```

### Унифицировать CI build path

CI (`perf-regression.yml`) должен использовать preset `bench` вместо ручного `cmake -B build`:

```yaml
- name: Configure and Build
  run: |
    cmake --preset bench
    cmake --build --preset bench --target bench_stage1 -j$(nproc)
```

Это даёт одинаковый `build/bench/benchmark/` путь локально и в CI.

---

## 5. CI / Local Split

### Mandatory (local, перед каждым PR)

```bash
make build PRESET=debug
make test PRESET=debug
make lint
```

### Mandatory (CI, автоматически на каждый PR)

- `pr-ci.yml`: quick-test + fuzz + lint + static-analysis
- `perf-regression.yml`: stage 1+2 perf regression check (conditional on changed paths)

### Recommended (local, для core/codegen изменений)

```bash
make test PRESET=asan
make perf-smoke          # NEW: stage 1+2 quick check against baseline
```

### Optional (local, по необходимости)

```bash
make test PRESET=tsan
make test PRESET=ubsan
make bench               # full performance_benchmark
make bench-report        # full report via unified runner
make fuzz
make profile
make docker-bench
```

---

## 6. Minimal Perf Smoke Design

### Цель

Быстрая (< 3 мин) проверка на регрессии в core runtime и codegen quality, идентичная тому, что делает CI в `perf-regression.yml`, но запускаемая локально одной командой.

### Реализация

Новый make target `perf-smoke`:

```makefile
perf-smoke:
	cmake --preset bench
	cmake --build --preset bench --target bench_all -j$$(nproc)
	python3 tools/katana_bench.py --stage all --format console \
		--compare benchmarks/baseline_stage1.json \
		--compare benchmarks/baseline_stage2.json \
		--threshold 0.05
```

**Примечание**: `tools/katana_bench.py` сейчас принимает один `--compare`. Нужно либо:
- (a) запускать два вызова (по одному на стадию), либо
- (b) добавить поддержку `--baseline-dir benchmarks/` и auto-pick по стадии.

Рекомендуется вариант (a) как минимальный:

```makefile
perf-smoke:
	cmake --preset bench
	cmake --build --preset bench --target bench_all -j$$(nproc)
	python3 tools/katana_bench.py --stage 1 --format console \
		--compare benchmarks/baseline_stage1.json --threshold 0.05
	python3 tools/katana_bench.py --stage 2 --format console \
		--compare benchmarks/baseline_stage2.json --threshold 0.05
```

### Контракт

- **Threshold**: 5% локально (CI использует 3% — более строгий, т.к. контролируемое окружение).
- **Exit code**: 0 = OK, 1 = regression detected.
- **Baseline**: файлы `benchmarks/baseline_stage1.json` и `benchmarks/baseline_stage2.json` (уже существуют в репо).
- **Build config**: Release (preset `bench`), clang/gcc, epoll backend.

---

## 7. Docs Updates Needed

| Файл | Что изменить |
|---|---|
| `README.md` §61 | Обновить бенчмарк-команду: убрать `--build-dir build/bench` (несуществующий флаг у `scripts/run_benchmarks.py`), использовать актуальный синтаксис |
| `README.md` §249 | Убрать ссылку на `docs/TESTING.md` (файл не существует) или создать файл |
| `CONTRIBUTING.md` | Добавить `make perf-smoke` в PR-Checklist (recommended для core/codegen) |
| `Makefile` | Добавить target `perf-smoke`; обновить `bench-report` → `scripts/run_benchmarks.py` вместо legacy `run_benchmarks.sh` |
| `CMakePresets.json` | Добавить test preset `bench` |
| `docs/BENCHMARKING.md` | Добавить секцию «Perf Smoke (quick local check)»; уточнить какой runner используется в CI |
| `tools/katana_bench.py` | Обновить error message в `find_build_dir()`: подсказывать `cmake --preset bench` вместо `cmake --preset debug` |
| `perf-regression.yml` | Перевести на `cmake --preset bench` для consistency (optional, не блокер) |

### Файлы для удаления / deprecation (Stage 3 scope — пометить, не удалять)

| Файл | Статус | Замена |
|---|---|---|
| `benchmark.sh` | Legacy | `make bench` / `cmake --preset bench` |
| `run_benchmarks.sh` | Legacy | `scripts/run_benchmarks.py --include-e2e` |
| `generate_benchmark_report.py` | Legacy | `scripts/run_benchmarks.py --update-docs` |

Рекомендация: добавить deprecation comment в начало каждого legacy файла, не удалять до Stage 4.

---

## Резюме изменений Stage 3

1. **Добавить `make perf-smoke`** — единый local perf smoke target.
2. **Добавить test preset `bench`** в CMakePresets.json.
3. **Обновить `make bench-report`** → использовать `scripts/run_benchmarks.py`.
4. **Обновить `tools/katana_bench.py` find_build_dir()** error message.
5. **Исправить README** — убрать битую ссылку на `docs/TESTING.md`, обновить bench команду.
6. **Обновить CONTRIBUTING.md** — добавить perf-smoke в checklist.
7. **Добавить deprecation headers** в legacy скрипты.
8. **Обновить docs/BENCHMARKING.md** — добавить perf smoke секцию.
