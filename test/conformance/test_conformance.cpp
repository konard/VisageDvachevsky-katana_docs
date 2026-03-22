// Stage 3 Conformance Harness for generated router/bindings.
//
// Tests the full generated HTTP pipeline (router → Content-Type/Accept
// negotiation → JSON parsing → validation → handler → serialization)
// against fixture-derived scenarios.
//
// Architecture:
//   conformance_api.yaml  →  katana_gen  →  generated/*.hpp
//   fixtures/*.json       →  test cases  →  assertions
//
// The stub handler returns minimal valid responses.
// Tests verify *framework* behaviour, not business logic.

#include "generated/generated_dtos.hpp"
#include "generated/generated_handlers.hpp"
#include "generated/generated_json.hpp"
#include "generated/generated_router_bindings.hpp"
#include "generated/generated_routes.hpp"
#include "generated/generated_validators.hpp"

#include "katana/core/arena.hpp"
#include "katana/core/http.hpp"
#include "katana/core/router.hpp"

#include "support/http_handler_harness.hpp"

#include <gtest/gtest.h>

using namespace katana;
using namespace katana::http;

// ============================================================
// Stub Handler — returns minimal valid responses
// ============================================================

struct conformance_stub_handler : generated::api_handler {
    katana::result<void> create_item(const CreateItemRequest& body, response& out) override {
        // Build a simple JSON response manually to avoid arena allocator issues in test code.
        std::string json = R"({"id":1,"name":")";
        json.append(std::string_view(body.name.data(), body.name.size()));
        json.append(R"(","quantity":)");
        json.append(std::to_string(body.quantity));
        json.append("}");
        out = response::json(std::move(json));
        return {};
    }

    katana::result<void> list_items(std::optional<int64_t> /*limit*/, response& out) override {
        out = response::json("[]");
        return {};
    }

    katana::result<void> get_item(int64_t id, response& out) override {
        std::string json = R"({"id":)";
        json.append(std::to_string(id));
        json.append(R"(,"name":null,"quantity":null})");
        out = response::json(std::move(json));
        return {};
    }

    katana::result<void> echo_body(const echo_body_request& body, response& out) override {
        std::string json = R"({"echo":")";
        json.append(std::string_view(body.message.data(), body.message.size()));
        json.append(R"("})");
        out = response::json(std::move(json));
        return {};
    }
};

// ============================================================
// Test Fixture — sets up generated router + harness
// ============================================================

class ConformanceTest : public ::testing::Test {
protected:
    void SetUp() override {
        router_bundle_ = std::make_unique<generated::generated_router>(handler_);
        harness_ = std::make_unique<test_support::HttpHandlerHarness>(
            router_handler(router_bundle_->router()));
    }

    // Build a raw HTTP request string from parts.
    static std::string build_raw_request(std::string_view method_str,
                                         std::string_view uri,
                                         const std::vector<std::pair<std::string, std::string>>& headers,
                                         std::string_view body) {
        std::string raw;
        raw.reserve(512);
        raw.append(method_str);
        raw.append(" ");
        raw.append(uri);
        raw.append(" HTTP/1.1\r\n");
        raw.append("Host: localhost\r\n");
        for (const auto& [name, value] : headers) {
            raw.append(name);
            raw.append(": ");
            raw.append(value);
            raw.append("\r\n");
        }
        if (!body.empty()) {
            raw.append("Content-Length: ");
            raw.append(std::to_string(body.size()));
            raw.append("\r\n");
        }
        raw.append("\r\n");
        raw.append(body);
        return raw;
    }

    http::response dispatch(std::string_view method_str,
                            std::string_view uri,
                            const std::vector<std::pair<std::string, std::string>>& headers,
                            std::string_view body) {
        return harness_->run_raw(build_raw_request(method_str, uri, headers, body));
    }

    conformance_stub_handler handler_;
    std::unique_ptr<generated::generated_router> router_bundle_;
    std::unique_ptr<test_support::HttpHandlerHarness> harness_;
};

// ============================================================
// 1. Valid Request Scenarios
// ============================================================

TEST_F(ConformanceTest, ValidCreateItem) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"name":"widget","quantity":10})");
    EXPECT_EQ(resp.status, 200);
    EXPECT_NE(resp.body.find("widget"), std::string::npos);
}

TEST_F(ConformanceTest, ValidCreateItemWithOptionalFields) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "*/*"}},
                         R"({"name":"gadget","quantity":5,"tag":"priority","email":"a@b.com"})");
    EXPECT_EQ(resp.status, 200);
}

TEST_F(ConformanceTest, ValidListItems) {
    auto resp = dispatch("GET", "/items",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 200);
    EXPECT_EQ(resp.body, "[]");
}

TEST_F(ConformanceTest, ValidGetItem) {
    auto resp = dispatch("GET", "/items/42",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 200);
    EXPECT_NE(resp.body.find("42"), std::string::npos);
}

TEST_F(ConformanceTest, ValidEcho) {
    auto resp = dispatch("POST", "/echo",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"message":"hello"})");
    EXPECT_EQ(resp.status, 200);
    EXPECT_NE(resp.body.find("hello"), std::string::npos);
}

TEST_F(ConformanceTest, NoAcceptHeaderDefaultsOk) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}},
                         R"({"name":"widget","quantity":10})");
    EXPECT_EQ(resp.status, 200);
}

// ============================================================
// 2. Missing Required Param / Field
// ============================================================

TEST_F(ConformanceTest, MissingRequiredFieldName) {
    // When a required field is absent from JSON, the parser returns nullopt,
    // so the error is "invalid request body" (parse-level), not a validation error.
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"quantity":10})");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("invalid request body"), std::string::npos);
}

TEST_F(ConformanceTest, EchoEmptyMessageViolatesMinLength) {
    auto resp = dispatch("POST", "/echo",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"message":""})");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("message"), std::string::npos);
}

// ============================================================
// 3. Invalid Param / Body
// ============================================================

TEST_F(ConformanceTest, InvalidBodyJson) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         "{not valid json");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("invalid request body"), std::string::npos);
}

TEST_F(ConformanceTest, ConstraintViolationQuantityTooLarge) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"name":"widget","quantity":99999})");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("quantity"), std::string::npos);
}

TEST_F(ConformanceTest, InvalidEmailFormat) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"name":"widget","quantity":5,"email":"not-an-email"})");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("email"), std::string::npos);
}

TEST_F(ConformanceTest, InvalidPathParamNonInteger) {
    auto resp = dispatch("GET", "/items/abc",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("id"), std::string::npos);
}

TEST_F(ConformanceTest, InvalidQueryParamNonInteger) {
    auto resp = dispatch("GET", "/items?limit=abc",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 400);
    EXPECT_NE(resp.body.find("limit"), std::string::npos);
}

// ============================================================
// 4. Unsupported Content-Type
// ============================================================

TEST_F(ConformanceTest, UnsupportedContentType) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/xml"}, {"Accept", "application/json"}},
                         "<item><name>widget</name></item>");
    EXPECT_EQ(resp.status, 415);
    EXPECT_NE(resp.body.find("unsupported Content-Type"), std::string::npos);
}

TEST_F(ConformanceTest, MissingContentType) {
    auto resp = dispatch("POST", "/items",
                         {{"Accept", "application/json"}},
                         R"({"name":"widget","quantity":10})");
    EXPECT_EQ(resp.status, 415);
    EXPECT_NE(resp.body.find("unsupported Content-Type"), std::string::npos);
}

// ============================================================
// 5. Unacceptable Accept
// ============================================================

TEST_F(ConformanceTest, UnacceptableAcceptHeader) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "text/xml"}},
                         R"({"name":"widget","quantity":10})");
    EXPECT_EQ(resp.status, 406);
    EXPECT_NE(resp.body.find("unsupported Accept"), std::string::npos);
}

// ============================================================
// 6. Response Media Type Selection
// ============================================================

TEST_F(ConformanceTest, ResponseContentTypeIsJson) {
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"name":"widget","quantity":10})");
    EXPECT_EQ(resp.status, 200);
    auto ct = resp.headers.get("Content-Type");
    ASSERT_TRUE(ct.has_value());
    EXPECT_NE(ct->find("application/json"), std::string_view::npos);
}

// ============================================================
// 7. Problem Details / Error Semantics
// ============================================================

TEST_F(ConformanceTest, ErrorResponseIsProblemJson) {
    // 415 error should produce a problem+json body with "status" and "title"
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/xml"}, {"Accept", "application/json"}},
                         "<xml/>");
    EXPECT_EQ(resp.status, 415);
    // problem_details.to_json() emits "status" and "title" keys
    EXPECT_NE(resp.body.find("\"status\""), std::string::npos);
    EXPECT_NE(resp.body.find("\"title\""), std::string::npos);
}

TEST_F(ConformanceTest, ValidationErrorContainsFieldAndDetail) {
    // Use a constraint violation (quantity out of range) to trigger the validator path.
    // When the required field is present but the constraint is violated,
    // the validator returns a field-level error with the field name.
    auto resp = dispatch("POST", "/items",
                         {{"Content-Type", "application/json"}, {"Accept", "application/json"}},
                         R"({"name":"widget","quantity":-1})");
    EXPECT_EQ(resp.status, 400);
    // Should contain the field name in the detail
    EXPECT_NE(resp.body.find("quantity"), std::string::npos);
    // Should be problem_details format
    EXPECT_NE(resp.body.find("\"status\""), std::string::npos);
}

// ============================================================
// 8. Route Dispatch — 404 / 405
// ============================================================

TEST_F(ConformanceTest, RouteNotFound) {
    auto resp = dispatch("GET", "/nonexistent",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 404);
}

TEST_F(ConformanceTest, MethodNotAllowed) {
    auto resp = dispatch("DELETE", "/items",
                         {{"Accept", "application/json"}}, "");
    EXPECT_EQ(resp.status, 405);
}
