// layer: flat
// Auto-generated validators from OpenAPI specification
//
// This file contains:
//   - Validation functions for all request/response types
//   - Format validators (email, UUID, date-time, etc.)
//   - Constraint validators (length, range, pattern, etc.)
//   - Enum value validators
//
// All validators return std::optional<validation_error>:
//   - std::nullopt on success
//   - validation_error with field path and error code on failure
//
// Validation is automatically called by router bindings before handler execution.
// Invalid requests return 400 Bad Request with error details.
//
#pragma once

#include "generated_dtos.hpp"
#include "katana/core/validation.hpp"
#include "katana/core/format_validators.hpp"
#include <algorithm>
#include <optional>
#include <string_view>
#include <string>
#include <cmath>
#include <cctype>
#include <regex>
#include <unordered_set>
#include <vector>

using katana::validation_error;
using katana::validation_error_code;

// ============================================================
// Format Validators (from framework)
// ============================================================

using katana::format_validators::is_valid_email;
using katana::format_validators::is_valid_uuid;
using katana::format_validators::is_valid_datetime;

// ============================================================
// Validation Functions
// ============================================================

[[nodiscard]] inline std::optional<validation_error> validate_CreateItemRequest(const CreateItemRequest& obj) {
    if (obj.name.empty()) {
        return validation_error{"name", validation_error_code::required_field_missing};
    }
    if (!obj.name.empty() && obj.name.size() < CreateItemRequest::metadata::NAME_MIN_LENGTH) {
        return validation_error{"name", validation_error_code::string_too_short, CreateItemRequest::metadata::NAME_MIN_LENGTH};
    }
    if (obj.name.size() > CreateItemRequest::metadata::NAME_MAX_LENGTH) {
        return validation_error{"name", validation_error_code::string_too_long, CreateItemRequest::metadata::NAME_MAX_LENGTH};
    }
    if (static_cast<double>(obj.quantity) < CreateItemRequest::metadata::QUANTITY_MINIMUM) {
        return validation_error{"quantity", validation_error_code::value_too_small, CreateItemRequest::metadata::QUANTITY_MINIMUM};
    }
    if (static_cast<double>(obj.quantity) > CreateItemRequest::metadata::QUANTITY_MAXIMUM) {
        return validation_error{"quantity", validation_error_code::value_too_large, CreateItemRequest::metadata::QUANTITY_MAXIMUM};
    }
    if (obj.email && !obj.email->empty() && !is_valid_email((*obj.email))) {
        return validation_error{"email", validation_error_code::invalid_email_format};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<validation_error> validate_ItemResponse(const ItemResponse& obj) {
    (void)obj;
    return std::nullopt;
}

[[nodiscard]] inline std::optional<validation_error> validate_list_items_response(const list_items_response& arr) {
    (void)arr;
    return std::nullopt;
}

[[nodiscard]] inline std::optional<validation_error> validate_echo_body_request(const echo_body_request& obj) {
    if (obj.message.empty()) {
        return validation_error{"message", validation_error_code::required_field_missing};
    }
    if (!obj.message.empty() && obj.message.size() < echo_body_request::metadata::MESSAGE_MIN_LENGTH) {
        return validation_error{"message", validation_error_code::string_too_short, echo_body_request::metadata::MESSAGE_MIN_LENGTH};
    }
    if (obj.message.size() > echo_body_request::metadata::MESSAGE_MAX_LENGTH) {
        return validation_error{"message", validation_error_code::string_too_long, echo_body_request::metadata::MESSAGE_MAX_LENGTH};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<validation_error> validate_echo_body_response(const echo_body_response& obj) {
    (void)obj;
    return std::nullopt;
}

