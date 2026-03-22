# Stage 3 Conformance Harness

## Overview

The conformance harness verifies that **generated router/bindings** produced by
`katana_gen` conform to the OpenAPI contract. It tests the full HTTP pipeline:
routing, Content-Type/Accept negotiation, JSON parsing, schema validation,
handler dispatch, and error semantics — all without external dependencies or a
running server.

## Architecture

```
conformance_api.yaml ──► katana_gen ──► generated/*.hpp
                                              │
                                              ▼
fixtures/*.json ──► test_conformance.cpp ──► generated_router
                         │                       │
                         │               router_handler adapter
                         │                       │
                         ▼                       ▼
                    assertions ◄── HttpHandlerHarness.run_raw()
```

**Key design decisions:**

1. **No reactor startup** — uses `HttpHandlerHarness` + `router_handler` to
   dispatch raw HTTP request strings through the generated router. Tests run in
   milliseconds.
2. **No external dependencies** — only the existing gtest-compatible harness,
   `katana_core`, and generated code.
3. **Stub handler** — returns minimal valid responses. Tests verify *framework*
   behaviour (negotiation, validation, error format), not business logic.
4. **Portable** — same CMake target works on Linux and WSL. No fork/bind/listen.

## Gap Analysis (Before This Harness)

| Area | Before | After |
|------|--------|-------|
| Valid request end-to-end | Codegen unit tests verify generated code text | Tests run generated code against real HTTP input |
| Content-Type / Accept negotiation | Only tested in router unit tests | Tested through generated bindings |
| Validation constraint errors | Validator unit tests with synthetic structs | Tested via JSON → parse → validate → error |
| Problem details format | `test_problem.cpp` tests `to_json()` | Verified end-to-end in HTTP response bodies |
| 404 / 405 dispatch | `test_router.cpp` with manual route tables | Verified through generated route tables |

## Fixture Format

Each scenario is a JSON file in `test/conformance/fixtures/`:

```json
{
  "name": "valid_create_item",
  "description": "POST /items with valid JSON body returns 200",
  "request": {
    "method": "POST",
    "uri": "/items",
    "headers": {
      "Content-Type": "application/json",
      "Accept": "application/json"
    },
    "body": "{\"name\":\"widget\",\"quantity\":10}"
  },
  "expected": {
    "status": 200,
    "content_type": "application/json",
    "body_contains": "widget"
  }
}
```

Fixtures are documentation — each one maps to a named C++ TEST_F case.

## Directory Layout

```
test/conformance/
├── conformance_api.yaml          # OpenAPI fixture spec
├── test_conformance.cpp          # C++ test runner (21 tests)
├── generated/                    # Pre-generated code (committed)
│   ├── generated_dtos.hpp
│   ├── generated_handlers.hpp
│   ├── generated_json.hpp
│   ├── generated_router_bindings.hpp
│   ├── generated_routes.hpp
│   └── generated_validators.hpp
└── fixtures/                     # Scenario descriptions (JSON)
    ├── valid_create_item.json
    ├── valid_create_item_with_optional.json
    ├── valid_list_items.json
    ├── valid_get_item.json
    ├── valid_echo.json
    ├── no_accept_defaults_ok.json
    ├── missing_required_field.json
    ├── echo_empty_message.json
    ├── invalid_body_json.json
    ├── constraint_violation_quantity.json
    ├── invalid_email_format.json
    ├── invalid_path_param.json
    ├── invalid_query_param.json
    ├── unsupported_content_type.json
    ├── missing_content_type.json
    ├── unacceptable_accept.json
    ├── route_not_found.json
    └── method_not_allowed.json
```

## Test Matrix (First Wave)

| # | Scenario | Category | Expected |
|---|----------|----------|----------|
| 1 | Valid POST /items | Valid request | 200 + JSON body |
| 2 | Valid POST /items with optional fields | Valid request | 200 |
| 3 | Valid GET /items | Valid request (no body) | 200 |
| 4 | Valid GET /items/42 | Valid request (path param) | 200 |
| 5 | Valid POST /echo | Valid request | 200 + echo body |
| 6 | POST /items without Accept | Valid (Accept defaults) | 200 |
| 7 | POST /items missing required field | Missing required param | 400 parse error |
| 8 | POST /echo empty message | Constraint violation (minLength) | 400 + field name |
| 9 | POST /items malformed JSON | Invalid body | 400 + "invalid request body" |
| 10 | POST /items quantity > max | Constraint violation | 400 + field name |
| 11 | POST /items invalid email | Format violation | 400 + field name |
| 12 | GET /items/abc (non-integer) | Invalid path param | 400 + "id" |
| 13 | GET /items?limit=abc | Invalid query param | 400 + "limit" |
| 14 | POST /items Content-Type: xml | Unsupported Content-Type | 415 |
| 15 | POST /items no Content-Type | Missing Content-Type | 415 |
| 16 | POST /items Accept: text/xml | Unacceptable Accept | 406 |
| 17 | Response Content-Type check | Response media type | application/json |
| 18 | 415 error body format | Problem details | has "status" + "title" |
| 19 | Validation error format | Problem details | has field + "status" |
| 20 | GET /nonexistent | Route not found | 404 |
| 21 | DELETE /items | Method not allowed | 405 |

## Running

```bash
# From build directory:
cmake --preset debug   # or: cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTING=ON
make conformance_tests -j$(nproc)
./test/conformance_tests

# Or via ctest:
ctest -R conformance
```

## Rollout Order

1. **Wave 1 (this PR):** 21 canonical scenarios covering all categories from the
   issue requirements. Generated code is pre-committed.
2. **Wave 2:** Add fixture-driven test runner that reads `fixtures/*.json` at
   runtime and generates test cases dynamically (data-driven).
3. **Wave 3:** Add coverage for multi-media-type negotiation (JSON + CBOR) when
   media type registry lands.
4. **Wave 4:** CI integration with automatic re-generation from spec changes.

## Definition of Done

- [x] Fixture format defined and documented
- [x] Test architecture uses existing test support (HttpHandlerHarness, router_handler)
- [x] No external dependencies beyond what is in the repo
- [x] All 7 canonical scenario categories covered (valid, missing required, invalid,
      Content-Type, Accept, response media type, problem details/error semantics)
- [x] Tests run identically on Linux and WSL (no fork/bind/listen)
- [x] Directory structure and naming convention documented
- [x] Conformance tests linked to generated artifacts via `generated/` directory
- [x] All 21 tests pass
