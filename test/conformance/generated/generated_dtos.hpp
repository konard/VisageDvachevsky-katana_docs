// layer: flat
// Auto-generated DTOs (Data Transfer Objects) from OpenAPI specification
//
// This file contains:
//   - Type definitions for request/response bodies
//   - Enum types with string conversion functions
//   - Compile-time metadata for validation constraints
//   - Zero-copy arena allocators for high performance
//
// All types include metadata structs with validation constraints:
//   - Required/optional flags
//   - String length constraints (min_length, max_length)
//   - Numeric constraints (minimum, maximum, exclusive bounds)
//   - Array constraints (min_items, max_items, uniqueness)
//
#pragma once

#include "katana/core/arena.hpp"
using katana::arena_allocator;
using katana::arena_string;
using katana::arena_vector;
using katana::monotonic_arena;

#include <optional>
#include <string_view>
#include <cctype>

#include <variant>

// ============================================================
// Enum Types
// ============================================================

/// Enum with 3 possible values
enum class CreateItemRequest_Tag_t_enum {
    normal,
    priority,
    archived
};

inline std::string_view to_string(CreateItemRequest_Tag_t_enum e) {
    switch (e) {
    case CreateItemRequest_Tag_t_enum::normal: return "normal";
    case CreateItemRequest_Tag_t_enum::priority: return "priority";
    case CreateItemRequest_Tag_t_enum::archived: return "archived";
    }
    return "";
}

inline std::optional<CreateItemRequest_Tag_t_enum> CreateItemRequest_Tag_t_enum_from_string(std::string_view s) {
    if (s == "normal") return CreateItemRequest_Tag_t_enum::normal;
    if (s == "priority") return CreateItemRequest_Tag_t_enum::priority;
    if (s == "archived") return CreateItemRequest_Tag_t_enum::archived;
    return std::nullopt;
}

// ============================================================
// Data Transfer Objects (DTOs)
// ============================================================

/// Data type with 4 fields
struct CreateItemRequest {
    // Compile-time metadata for validation
    struct metadata {
        static constexpr bool NAME_REQUIRED = true;
        static constexpr size_t NAME_MIN_LENGTH = 1;
        static constexpr size_t NAME_MAX_LENGTH = 128;
        static constexpr bool QUANTITY_REQUIRED = true;
        static constexpr double QUANTITY_MINIMUM = 0;
        static constexpr double QUANTITY_MAXIMUM = 10000;
        static constexpr bool TAG_REQUIRED = false;
        static constexpr bool EMAIL_REQUIRED = false;
    };

    static_assert(metadata::NAME_MIN_LENGTH <= metadata::NAME_MAX_LENGTH, "name: min_length must be <= max_length");
    static_assert(metadata::QUANTITY_MINIMUM <= metadata::QUANTITY_MAXIMUM, "quantity: minimum must be <= maximum");

    explicit CreateItemRequest(monotonic_arena* arena = nullptr)
        : arena_(arena),
          name(arena_allocator<char>(arena)) {}

    monotonic_arena* arena_;
    arena_string<> name;
    int64_t quantity;
    /// Optional field
    std::optional<CreateItemRequest_Tag_t_enum> tag;
    /// Optional field
    std::optional<arena_string<>> email;
};

using CreateItemRequest_Name_t = arena_string<>;

using CreateItemRequest_Quantity_t = int64_t;

using CreateItemRequest_Tag_t = CreateItemRequest_Tag_t_enum;

using CreateItemRequest_Email_t = arena_string<>;

/// Data type with 3 fields
struct ItemResponse {
    // Compile-time metadata for validation
    struct metadata {
        static constexpr bool ID_REQUIRED = false;
        static constexpr bool NAME_REQUIRED = false;
        static constexpr bool QUANTITY_REQUIRED = false;
    };


    explicit ItemResponse(monotonic_arena* arena = nullptr)
        : arena_(arena) {}

    monotonic_arena* arena_;
    /// Optional field
    std::optional<int64_t> id;
    /// Optional field
    std::optional<arena_string<>> name;
    /// Optional field
    std::optional<int64_t> quantity;
};

using ItemResponse_Id_t = int64_t;

using ItemResponse_Name_t = arena_string<>;

using ItemResponse_Quantity_t = int64_t;

using schema = std::monostate;

using schema_1 = std::monostate;

using list_items_param_limit = int64_t;

using schema_2 = std::monostate;

using get_item_param_id = int64_t;

using schema_3 = std::monostate;

/// Request body type with 1 fields
struct echo_body_request {
    // Compile-time metadata for validation
    struct metadata {
        static constexpr bool MESSAGE_REQUIRED = true;
        static constexpr size_t MESSAGE_MIN_LENGTH = 1;
        static constexpr size_t MESSAGE_MAX_LENGTH = 256;
    };

    static_assert(metadata::MESSAGE_MIN_LENGTH <= metadata::MESSAGE_MAX_LENGTH, "message: min_length must be <= max_length");

    explicit echo_body_request(monotonic_arena* arena = nullptr)
        : arena_(arena),
          message(arena_allocator<char>(arena)) {}

    monotonic_arena* arena_;
    arena_string<> message;
};

using echo_body_request_Message = arena_string<>;

/// Response body type with 1 fields
struct echo_body_response {
    // Compile-time metadata for validation
    struct metadata {
        static constexpr bool ECHO_REQUIRED = false;
    };


    explicit echo_body_response(monotonic_arena* arena = nullptr)
        : arena_(arena) {}

    monotonic_arena* arena_;
    /// Optional field
    std::optional<arena_string<>> echo;
};

using echo_body_response_Echo = arena_string<>;

using list_items_response = arena_vector<ItemResponse>;

