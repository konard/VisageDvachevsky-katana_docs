// layer: flat
#pragma once

#include "katana/core/http.hpp"
#include "katana/core/http_utils.hpp"
#include "katana/core/router.hpp"
#include <array>
#include <span>
#include <string_view>

namespace generated {

using katana::http_utils::content_type_info;

struct route_entry {
    std::string_view path;
    katana::http::method method;
    std::string_view operation_id;
    std::span<const content_type_info> consumes;
    std::span<const content_type_info> produces;
};

inline constexpr content_type_info route_0_consumes[] = {
    {"application/json"},
};

inline constexpr content_type_info route_0_produces[] = {
    {"application/json"},
};

inline constexpr content_type_info route_1_produces[] = {
    {"application/json"},
};

inline constexpr content_type_info route_2_produces[] = {
    {"application/json"},
};

inline constexpr content_type_info route_3_consumes[] = {
    {"application/json"},
};

inline constexpr content_type_info route_3_produces[] = {
    {"application/json"},
};

inline constexpr route_entry routes[] = {
    {"/items", katana::http::method::post, "create_item", route_0_consumes, route_0_produces},
    {"/items", katana::http::method::get, "list_items", {}, route_1_produces},
    {"/items/{id}", katana::http::method::get, "get_item", {}, route_2_produces},
    {"/echo", katana::http::method::post, "echo_body", route_3_consumes, route_3_produces},
};

inline constexpr size_t route_count = sizeof(routes) / sizeof(routes[0]);

// Compile-time route metadata for type safety
namespace route_metadata {
    // create_item: POST /items
    struct create_item_metadata {
        static constexpr std::string_view path = "/items";
        static constexpr katana::http::method method = katana::http::method::post;
        static constexpr std::string_view operation_id = "create_item";
        static constexpr size_t path_param_count = 0;
        static constexpr bool has_request_body = true;
    };

    // list_items: GET /items
    struct list_items_metadata {
        static constexpr std::string_view path = "/items";
        static constexpr katana::http::method method = katana::http::method::get;
        static constexpr std::string_view operation_id = "list_items";
        static constexpr size_t path_param_count = 0;
        static constexpr bool has_request_body = false;
    };

    // get_item: GET /items/{id}
    struct get_item_metadata {
        static constexpr std::string_view path = "/items/{id}";
        static constexpr katana::http::method method = katana::http::method::get;
        static constexpr std::string_view operation_id = "get_item";
        static constexpr size_t path_param_count = 1;
        static constexpr bool has_request_body = false;
    };

    // echo_body: POST /echo
    struct echo_body_metadata {
        static constexpr std::string_view path = "/echo";
        static constexpr katana::http::method method = katana::http::method::post;
        static constexpr std::string_view operation_id = "echo_body";
        static constexpr size_t path_param_count = 0;
        static constexpr bool has_request_body = true;
    };

} // namespace route_metadata

// Compile-time validations
static_assert(route_count > 0, "At least one route must be defined");
} // namespace generated
