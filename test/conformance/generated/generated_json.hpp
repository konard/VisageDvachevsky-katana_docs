// layer: flat
// Auto-generated JSON parsers and serializers from OpenAPI specification
//
// This file contains:
//   - parse_<Type>() functions: JSON string → C++ struct
//   - serialize_<Type>() functions: C++ struct → JSON string
//
// Features:
//   - Zero-copy parsing using arena allocators
//   - Streaming JSON generation without intermediate buffers
//   - Type-safe enum conversion
//   - Automatic null handling for optional fields
//
// All parse functions return std::optional<T>:
//   - std::nullopt on parse error (invalid JSON, wrong type, etc.)
//   - Parsed object on success
//
#pragma once

#include "katana/core/arena.hpp"
#include "katana/core/serde.hpp"
#include <optional>
#include <string>
#include <charconv>
#include <vector>

using katana::monotonic_arena;

// ============================================================
// Forward Declarations
// ============================================================

[[nodiscard]] inline std::optional<CreateItemRequest> parse_CreateItemRequest(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Name_t> parse_CreateItemRequest_Name_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Quantity_t> parse_CreateItemRequest_Quantity_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Tag_t> parse_CreateItemRequest_Tag_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Email_t> parse_CreateItemRequest_Email_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse> parse_ItemResponse(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Id_t> parse_ItemResponse_Id_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Name_t> parse_ItemResponse_Name_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Quantity_t> parse_ItemResponse_Quantity_t(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema> parse_schema(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_1> parse_schema_1(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<list_items_param_limit> parse_list_items_param_limit(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<list_items_response> parse_list_items_response(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_2> parse_schema_2(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<get_item_param_id> parse_get_item_param_id(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_3> parse_schema_3(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_request> parse_echo_body_request(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_request_Message> parse_echo_body_request_Message(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_response> parse_echo_body_response(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_response_Echo> parse_echo_body_response_Echo(std::string_view json, monotonic_arena* arena);

[[nodiscard]] inline std::optional<CreateItemRequest> parse_CreateItemRequest(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Name_t> parse_CreateItemRequest_Name_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Quantity_t> parse_CreateItemRequest_Quantity_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Tag_t> parse_CreateItemRequest_Tag_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<CreateItemRequest_Email_t> parse_CreateItemRequest_Email_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse> parse_ItemResponse(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Id_t> parse_ItemResponse_Id_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Name_t> parse_ItemResponse_Name_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<ItemResponse_Quantity_t> parse_ItemResponse_Quantity_t(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema> parse_schema(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_1> parse_schema_1(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<list_items_param_limit> parse_list_items_param_limit(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<list_items_response> parse_list_items_response(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_2> parse_schema_2(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<get_item_param_id> parse_get_item_param_id(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<schema_3> parse_schema_3(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_request> parse_echo_body_request(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_request_Message> parse_echo_body_request_Message(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_response> parse_echo_body_response(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<echo_body_response_Echo> parse_echo_body_response_Echo(katana::serde::json_cursor& cur, monotonic_arena* arena);

inline void serialize_CreateItemRequest_into(const CreateItemRequest& obj, std::string& out);
inline void serialize_CreateItemRequest_Name_t_into(const CreateItemRequest_Name_t& obj, std::string& out);
inline void serialize_CreateItemRequest_Quantity_t_into(const CreateItemRequest_Quantity_t& obj, std::string& out);
inline void serialize_CreateItemRequest_Tag_t_into(const CreateItemRequest_Tag_t& obj, std::string& out);
inline void serialize_CreateItemRequest_Email_t_into(const CreateItemRequest_Email_t& obj, std::string& out);
inline void serialize_ItemResponse_into(const ItemResponse& obj, std::string& out);
inline void serialize_ItemResponse_Id_t_into(const ItemResponse_Id_t& obj, std::string& out);
inline void serialize_ItemResponse_Name_t_into(const ItemResponse_Name_t& obj, std::string& out);
inline void serialize_ItemResponse_Quantity_t_into(const ItemResponse_Quantity_t& obj, std::string& out);
inline void serialize_schema_into(const schema& obj, std::string& out);
inline void serialize_schema_1_into(const schema_1& obj, std::string& out);
inline void serialize_list_items_param_limit_into(const list_items_param_limit& obj, std::string& out);
inline void serialize_list_items_response_into(const list_items_response& obj, std::string& out);
inline void serialize_schema_2_into(const schema_2& obj, std::string& out);
inline void serialize_get_item_param_id_into(const get_item_param_id& obj, std::string& out);
inline void serialize_schema_3_into(const schema_3& obj, std::string& out);
inline void serialize_echo_body_request_into(const echo_body_request& obj, std::string& out);
inline void serialize_echo_body_request_Message_into(const echo_body_request_Message& obj, std::string& out);
inline void serialize_echo_body_response_into(const echo_body_response& obj, std::string& out);
inline void serialize_echo_body_response_Echo_into(const echo_body_response_Echo& obj, std::string& out);

inline std::string serialize_CreateItemRequest(const CreateItemRequest& obj);
inline std::string serialize_CreateItemRequest_Name_t(const CreateItemRequest_Name_t& obj);
inline std::string serialize_CreateItemRequest_Quantity_t(const CreateItemRequest_Quantity_t& obj);
inline std::string serialize_CreateItemRequest_Tag_t(const CreateItemRequest_Tag_t& obj);
inline std::string serialize_CreateItemRequest_Email_t(const CreateItemRequest_Email_t& obj);
inline std::string serialize_ItemResponse(const ItemResponse& obj);
inline std::string serialize_ItemResponse_Id_t(const ItemResponse_Id_t& obj);
inline std::string serialize_ItemResponse_Name_t(const ItemResponse_Name_t& obj);
inline std::string serialize_ItemResponse_Quantity_t(const ItemResponse_Quantity_t& obj);
inline std::string serialize_schema(const schema& obj);
inline std::string serialize_schema_1(const schema_1& obj);
inline std::string serialize_list_items_param_limit(const list_items_param_limit& obj);
inline std::string serialize_list_items_response(const list_items_response& obj);
inline std::string serialize_schema_2(const schema_2& obj);
inline std::string serialize_get_item_param_id(const get_item_param_id& obj);
inline std::string serialize_schema_3(const schema_3& obj);
inline std::string serialize_echo_body_request(const echo_body_request& obj);
inline std::string serialize_echo_body_request_Message(const echo_body_request_Message& obj);
inline std::string serialize_echo_body_response(const echo_body_response& obj);
inline std::string serialize_echo_body_response_Echo(const echo_body_response_Echo& obj);

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest>> parse_CreateItemRequest_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Name_t>> parse_CreateItemRequest_Name_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Quantity_t>> parse_CreateItemRequest_Quantity_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Tag_t>> parse_CreateItemRequest_Tag_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Email_t>> parse_CreateItemRequest_Email_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse>> parse_ItemResponse_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Id_t>> parse_ItemResponse_Id_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Name_t>> parse_ItemResponse_Name_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Quantity_t>> parse_ItemResponse_Quantity_t_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema>> parse_schema_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_1>> parse_schema_1_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<list_items_param_limit>> parse_list_items_param_limit_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<list_items_response>> parse_list_items_response_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_2>> parse_schema_2_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<get_item_param_id>> parse_get_item_param_id_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_3>> parse_schema_3_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_request>> parse_echo_body_request_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_request_Message>> parse_echo_body_request_Message_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_response>> parse_echo_body_response_array(std::string_view json, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_response_Echo>> parse_echo_body_response_Echo_array(std::string_view json, monotonic_arena* arena);

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest>> parse_CreateItemRequest_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Name_t>> parse_CreateItemRequest_Name_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Quantity_t>> parse_CreateItemRequest_Quantity_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Tag_t>> parse_CreateItemRequest_Tag_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Email_t>> parse_CreateItemRequest_Email_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse>> parse_ItemResponse_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Id_t>> parse_ItemResponse_Id_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Name_t>> parse_ItemResponse_Name_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<ItemResponse_Quantity_t>> parse_ItemResponse_Quantity_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema>> parse_schema_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_1>> parse_schema_1_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<list_items_param_limit>> parse_list_items_param_limit_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<list_items_response>> parse_list_items_response_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_2>> parse_schema_2_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<get_item_param_id>> parse_get_item_param_id_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<schema_3>> parse_schema_3_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_request>> parse_echo_body_request_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_request_Message>> parse_echo_body_request_Message_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_response>> parse_echo_body_response_array(katana::serde::json_cursor& cur, monotonic_arena* arena);
[[nodiscard]] inline std::optional<std::vector<echo_body_response_Echo>> parse_echo_body_response_Echo_array(katana::serde::json_cursor& cur, monotonic_arena* arena);

inline void serialize_CreateItemRequest_array_into(const std::vector<CreateItemRequest>& arr, std::string& out);
inline void serialize_CreateItemRequest_array_into(const arena_vector<CreateItemRequest>& arr, std::string& out);
inline void serialize_CreateItemRequest_Name_t_array_into(const std::vector<CreateItemRequest_Name_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Name_t_array_into(const arena_vector<CreateItemRequest_Name_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Quantity_t_array_into(const std::vector<CreateItemRequest_Quantity_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Quantity_t_array_into(const arena_vector<CreateItemRequest_Quantity_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Tag_t_array_into(const std::vector<CreateItemRequest_Tag_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Tag_t_array_into(const arena_vector<CreateItemRequest_Tag_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Email_t_array_into(const std::vector<CreateItemRequest_Email_t>& arr, std::string& out);
inline void serialize_CreateItemRequest_Email_t_array_into(const arena_vector<CreateItemRequest_Email_t>& arr, std::string& out);
inline void serialize_ItemResponse_array_into(const std::vector<ItemResponse>& arr, std::string& out);
inline void serialize_ItemResponse_array_into(const arena_vector<ItemResponse>& arr, std::string& out);
inline void serialize_ItemResponse_Id_t_array_into(const std::vector<ItemResponse_Id_t>& arr, std::string& out);
inline void serialize_ItemResponse_Id_t_array_into(const arena_vector<ItemResponse_Id_t>& arr, std::string& out);
inline void serialize_ItemResponse_Name_t_array_into(const std::vector<ItemResponse_Name_t>& arr, std::string& out);
inline void serialize_ItemResponse_Name_t_array_into(const arena_vector<ItemResponse_Name_t>& arr, std::string& out);
inline void serialize_ItemResponse_Quantity_t_array_into(const std::vector<ItemResponse_Quantity_t>& arr, std::string& out);
inline void serialize_ItemResponse_Quantity_t_array_into(const arena_vector<ItemResponse_Quantity_t>& arr, std::string& out);
inline void serialize_schema_array_into(const std::vector<schema>& arr, std::string& out);
inline void serialize_schema_array_into(const arena_vector<schema>& arr, std::string& out);
inline void serialize_schema_1_array_into(const std::vector<schema_1>& arr, std::string& out);
inline void serialize_schema_1_array_into(const arena_vector<schema_1>& arr, std::string& out);
inline void serialize_list_items_param_limit_array_into(const std::vector<list_items_param_limit>& arr, std::string& out);
inline void serialize_list_items_param_limit_array_into(const arena_vector<list_items_param_limit>& arr, std::string& out);
inline void serialize_list_items_response_array_into(const std::vector<list_items_response>& arr, std::string& out);
inline void serialize_list_items_response_array_into(const arena_vector<list_items_response>& arr, std::string& out);
inline void serialize_schema_2_array_into(const std::vector<schema_2>& arr, std::string& out);
inline void serialize_schema_2_array_into(const arena_vector<schema_2>& arr, std::string& out);
inline void serialize_get_item_param_id_array_into(const std::vector<get_item_param_id>& arr, std::string& out);
inline void serialize_get_item_param_id_array_into(const arena_vector<get_item_param_id>& arr, std::string& out);
inline void serialize_schema_3_array_into(const std::vector<schema_3>& arr, std::string& out);
inline void serialize_schema_3_array_into(const arena_vector<schema_3>& arr, std::string& out);
inline void serialize_echo_body_request_array_into(const std::vector<echo_body_request>& arr, std::string& out);
inline void serialize_echo_body_request_array_into(const arena_vector<echo_body_request>& arr, std::string& out);
inline void serialize_echo_body_request_Message_array_into(const std::vector<echo_body_request_Message>& arr, std::string& out);
inline void serialize_echo_body_request_Message_array_into(const arena_vector<echo_body_request_Message>& arr, std::string& out);
inline void serialize_echo_body_response_array_into(const std::vector<echo_body_response>& arr, std::string& out);
inline void serialize_echo_body_response_array_into(const arena_vector<echo_body_response>& arr, std::string& out);
inline void serialize_echo_body_response_Echo_array_into(const std::vector<echo_body_response_Echo>& arr, std::string& out);
inline void serialize_echo_body_response_Echo_array_into(const arena_vector<echo_body_response_Echo>& arr, std::string& out);

inline std::string serialize_CreateItemRequest_array(const std::vector<CreateItemRequest>& arr);
inline std::string serialize_CreateItemRequest_array(const arena_vector<CreateItemRequest>& arr);
inline std::string serialize_CreateItemRequest_Name_t_array(const std::vector<CreateItemRequest_Name_t>& arr);
inline std::string serialize_CreateItemRequest_Name_t_array(const arena_vector<CreateItemRequest_Name_t>& arr);
inline std::string serialize_CreateItemRequest_Quantity_t_array(const std::vector<CreateItemRequest_Quantity_t>& arr);
inline std::string serialize_CreateItemRequest_Quantity_t_array(const arena_vector<CreateItemRequest_Quantity_t>& arr);
inline std::string serialize_CreateItemRequest_Tag_t_array(const std::vector<CreateItemRequest_Tag_t>& arr);
inline std::string serialize_CreateItemRequest_Tag_t_array(const arena_vector<CreateItemRequest_Tag_t>& arr);
inline std::string serialize_CreateItemRequest_Email_t_array(const std::vector<CreateItemRequest_Email_t>& arr);
inline std::string serialize_CreateItemRequest_Email_t_array(const arena_vector<CreateItemRequest_Email_t>& arr);
inline std::string serialize_ItemResponse_array(const std::vector<ItemResponse>& arr);
inline std::string serialize_ItemResponse_array(const arena_vector<ItemResponse>& arr);
inline std::string serialize_ItemResponse_Id_t_array(const std::vector<ItemResponse_Id_t>& arr);
inline std::string serialize_ItemResponse_Id_t_array(const arena_vector<ItemResponse_Id_t>& arr);
inline std::string serialize_ItemResponse_Name_t_array(const std::vector<ItemResponse_Name_t>& arr);
inline std::string serialize_ItemResponse_Name_t_array(const arena_vector<ItemResponse_Name_t>& arr);
inline std::string serialize_ItemResponse_Quantity_t_array(const std::vector<ItemResponse_Quantity_t>& arr);
inline std::string serialize_ItemResponse_Quantity_t_array(const arena_vector<ItemResponse_Quantity_t>& arr);
inline std::string serialize_schema_array(const std::vector<schema>& arr);
inline std::string serialize_schema_array(const arena_vector<schema>& arr);
inline std::string serialize_schema_1_array(const std::vector<schema_1>& arr);
inline std::string serialize_schema_1_array(const arena_vector<schema_1>& arr);
inline std::string serialize_list_items_param_limit_array(const std::vector<list_items_param_limit>& arr);
inline std::string serialize_list_items_param_limit_array(const arena_vector<list_items_param_limit>& arr);
inline std::string serialize_list_items_response_array(const std::vector<list_items_response>& arr);
inline std::string serialize_list_items_response_array(const arena_vector<list_items_response>& arr);
inline std::string serialize_schema_2_array(const std::vector<schema_2>& arr);
inline std::string serialize_schema_2_array(const arena_vector<schema_2>& arr);
inline std::string serialize_get_item_param_id_array(const std::vector<get_item_param_id>& arr);
inline std::string serialize_get_item_param_id_array(const arena_vector<get_item_param_id>& arr);
inline std::string serialize_schema_3_array(const std::vector<schema_3>& arr);
inline std::string serialize_schema_3_array(const arena_vector<schema_3>& arr);
inline std::string serialize_echo_body_request_array(const std::vector<echo_body_request>& arr);
inline std::string serialize_echo_body_request_array(const arena_vector<echo_body_request>& arr);
inline std::string serialize_echo_body_request_Message_array(const std::vector<echo_body_request_Message>& arr);
inline std::string serialize_echo_body_request_Message_array(const arena_vector<echo_body_request_Message>& arr);
inline std::string serialize_echo_body_response_array(const std::vector<echo_body_response>& arr);
inline std::string serialize_echo_body_response_array(const arena_vector<echo_body_response>& arr);
inline std::string serialize_echo_body_response_Echo_array(const std::vector<echo_body_response_Echo>& arr);
inline std::string serialize_echo_body_response_Echo_array(const arena_vector<echo_body_response_Echo>& arr);

// ============================================================
// JSON Parse Functions
// ============================================================

[[nodiscard]] inline std::optional<CreateItemRequest> parse_CreateItemRequest(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_object_start()) return std::nullopt;

    CreateItemRequest obj(arena);
    bool has_name = false;
    bool has_quantity = false;

    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) break;

        switch (key->size()) {
        case 3:
            if (*key == "tag") {
                if (auto v = cur.string()) {
                    auto enum_val = CreateItemRequest_Tag_t_enum_from_string(std::string_view(v->begin(), v->end()));
                    if (enum_val) obj.tag = *enum_val;
                } else { cur.skip_value(); }
            } else { cur.skip_value(); }
            break;
        case 4:
            if (*key == "name") {
                has_name = true;
                if (auto v = cur.string()) {
                    obj.name = arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena));
                } else { cur.skip_value(); }
            } else { cur.skip_value(); }
            break;
        case 5:
            if (*key == "email") {
                if (auto v = cur.string()) {
                    obj.email = arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena));
                } else { cur.skip_value(); }
            } else { cur.skip_value(); }
            break;
        case 8:
            if (*key == "quantity") {
                has_quantity = true;
                if (auto v = katana::serde::parse_int64(cur)) {
                    obj.quantity = *v;
                } else { cur.skip_value(); }
            } else { cur.skip_value(); }
            break;
        default:
            cur.skip_value();
            break;
        }
        cur.try_comma();
    }
    if (!has_name) return std::nullopt;
    if (!has_quantity) return std::nullopt;
    return obj;
}

[[nodiscard]] inline std::optional<CreateItemRequest> parse_CreateItemRequest(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest(cur, arena);
}

[[nodiscard]] inline std::optional<CreateItemRequest_Name_t> parse_CreateItemRequest_Name_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (auto v = cur.string()) {
        return CreateItemRequest_Name_t{arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena))};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<CreateItemRequest_Name_t> parse_CreateItemRequest_Name_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Name_t(cur, arena);
}

[[nodiscard]] inline std::optional<CreateItemRequest_Quantity_t> parse_CreateItemRequest_Quantity_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = katana::serde::parse_int64(cur)) return CreateItemRequest_Quantity_t{*v};
    return std::nullopt;
}

[[nodiscard]] inline std::optional<CreateItemRequest_Quantity_t> parse_CreateItemRequest_Quantity_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Quantity_t(cur, arena);
}

[[nodiscard]] inline std::optional<CreateItemRequest_Tag_t> parse_CreateItemRequest_Tag_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = cur.string()) {
        return CreateItemRequest_Tag_t_enum_from_string(std::string_view(v->begin(), v->end()));
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<CreateItemRequest_Tag_t> parse_CreateItemRequest_Tag_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Tag_t(cur, arena);
}

[[nodiscard]] inline std::optional<CreateItemRequest_Email_t> parse_CreateItemRequest_Email_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (auto v = cur.string()) {
        return CreateItemRequest_Email_t{arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena))};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<CreateItemRequest_Email_t> parse_CreateItemRequest_Email_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Email_t(cur, arena);
}

[[nodiscard]] inline std::optional<ItemResponse> parse_ItemResponse(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_object_start()) return std::nullopt;

    ItemResponse obj(arena);

    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) break;

        if (*key == "id") {
            if (auto v = katana::serde::parse_int64(cur)) {
                obj.id = *v;
            } else { cur.skip_value(); }
        } else         if (*key == "name") {
            if (auto v = cur.string()) {
                obj.name = arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena));
            } else { cur.skip_value(); }
        } else         if (*key == "quantity") {
            if (auto v = katana::serde::parse_int64(cur)) {
                obj.quantity = *v;
            } else { cur.skip_value(); }
        } else {
            cur.skip_value();
        }
        cur.try_comma();
    }
    return obj;
}

[[nodiscard]] inline std::optional<ItemResponse> parse_ItemResponse(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse(cur, arena);
}

[[nodiscard]] inline std::optional<ItemResponse_Id_t> parse_ItemResponse_Id_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = katana::serde::parse_int64(cur)) return ItemResponse_Id_t{*v};
    return std::nullopt;
}

[[nodiscard]] inline std::optional<ItemResponse_Id_t> parse_ItemResponse_Id_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Id_t(cur, arena);
}

[[nodiscard]] inline std::optional<ItemResponse_Name_t> parse_ItemResponse_Name_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (auto v = cur.string()) {
        return ItemResponse_Name_t{arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena))};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<ItemResponse_Name_t> parse_ItemResponse_Name_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Name_t(cur, arena);
}

[[nodiscard]] inline std::optional<ItemResponse_Quantity_t> parse_ItemResponse_Quantity_t(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = katana::serde::parse_int64(cur)) return ItemResponse_Quantity_t{*v};
    return std::nullopt;
}

[[nodiscard]] inline std::optional<ItemResponse_Quantity_t> parse_ItemResponse_Quantity_t(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Quantity_t(cur, arena);
}

[[nodiscard]] inline std::optional<schema> parse_schema(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (!cur.try_object_start()) {
        cur.skip_value();
        return std::nullopt;
    }
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) {
            return std::nullopt;
        }
        cur.skip_value();
        cur.try_comma();
    }
    return schema{};
}

[[nodiscard]] inline std::optional<schema> parse_schema(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema(cur, arena);
}

[[nodiscard]] inline std::optional<schema_1> parse_schema_1(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (!cur.try_object_start()) {
        cur.skip_value();
        return std::nullopt;
    }
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) {
            return std::nullopt;
        }
        cur.skip_value();
        cur.try_comma();
    }
    return schema_1{};
}

[[nodiscard]] inline std::optional<schema_1> parse_schema_1(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_1(cur, arena);
}

[[nodiscard]] inline std::optional<list_items_param_limit> parse_list_items_param_limit(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = katana::serde::parse_int64(cur)) return list_items_param_limit{*v};
    return std::nullopt;
}

[[nodiscard]] inline std::optional<list_items_param_limit> parse_list_items_param_limit(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_list_items_param_limit(cur, arena);
}

[[nodiscard]] inline std::optional<list_items_response> parse_list_items_response(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;
    list_items_response result{arena_allocator<ItemResponse>(arena)};
    size_t reserve_hint = 0;
    for (const char* p = cur.ptr; p < cur.end; ++p) {
        if (*p == ',') ++reserve_hint;
    }
    if (cur.ptr < cur.end && *cur.ptr != ']') ++reserve_hint;
    result.reserve(reserve_hint);
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        if (auto parsed = parse_ItemResponse(cur, arena)) result.push_back(std::move(*parsed));
        else cur.skip_value();
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<list_items_response> parse_list_items_response(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    if (!cur.try_array_start()) return std::nullopt;
    list_items_response result{arena_allocator<ItemResponse>(arena)};
    size_t reserve_hint = 0;
    for (char ch : json) {
        if (ch == ',') ++reserve_hint;
    }
    if (!json.empty() && json != "[]") ++reserve_hint;
    result.reserve(reserve_hint);
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        if (auto parsed = parse_ItemResponse(cur, arena)) result.push_back(std::move(*parsed));
        else cur.skip_value();
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<schema_2> parse_schema_2(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (!cur.try_object_start()) {
        cur.skip_value();
        return std::nullopt;
    }
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) {
            return std::nullopt;
        }
        cur.skip_value();
        cur.try_comma();
    }
    return schema_2{};
}

[[nodiscard]] inline std::optional<schema_2> parse_schema_2(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_2(cur, arena);
}

[[nodiscard]] inline std::optional<get_item_param_id> parse_get_item_param_id(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (auto v = katana::serde::parse_int64(cur)) return get_item_param_id{*v};
    return std::nullopt;
}

[[nodiscard]] inline std::optional<get_item_param_id> parse_get_item_param_id(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_get_item_param_id(cur, arena);
}

[[nodiscard]] inline std::optional<schema_3> parse_schema_3(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    (void)arena;
    if (!cur.try_object_start()) {
        cur.skip_value();
        return std::nullopt;
    }
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) {
            return std::nullopt;
        }
        cur.skip_value();
        cur.try_comma();
    }
    return schema_3{};
}

[[nodiscard]] inline std::optional<schema_3> parse_schema_3(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_3(cur, arena);
}

[[nodiscard]] inline std::optional<echo_body_request> parse_echo_body_request(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_object_start()) return std::nullopt;

    echo_body_request obj(arena);
    bool has_message = false;

    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) break;

        if (*key == "message") {
            has_message = true;
            if (auto v = cur.string()) {
                obj.message = arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena));
            } else { cur.skip_value(); }
        } else {
            cur.skip_value();
        }
        cur.try_comma();
    }
    if (!has_message) return std::nullopt;
    return obj;
}

[[nodiscard]] inline std::optional<echo_body_request> parse_echo_body_request(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_request(cur, arena);
}

[[nodiscard]] inline std::optional<echo_body_request_Message> parse_echo_body_request_Message(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (auto v = cur.string()) {
        return echo_body_request_Message{arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena))};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<echo_body_request_Message> parse_echo_body_request_Message(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_request_Message(cur, arena);
}

[[nodiscard]] inline std::optional<echo_body_response> parse_echo_body_response(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_object_start()) return std::nullopt;

    echo_body_response obj(arena);

    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_object_end()) break;
        auto key = cur.string();
        if (!key || !cur.consume(':')) break;

        if (*key == "echo") {
            if (auto v = cur.string()) {
                obj.echo = arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena));
            } else { cur.skip_value(); }
        } else {
            cur.skip_value();
        }
        cur.try_comma();
    }
    return obj;
}

[[nodiscard]] inline std::optional<echo_body_response> parse_echo_body_response(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_response(cur, arena);
}

[[nodiscard]] inline std::optional<echo_body_response_Echo> parse_echo_body_response_Echo(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (auto v = cur.string()) {
        return echo_body_response_Echo{arena_string<>(v->begin(), v->end(), arena_allocator<char>(arena))};
    }
    return std::nullopt;
}

[[nodiscard]] inline std::optional<echo_body_response_Echo> parse_echo_body_response_Echo(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_response_Echo(cur, arena);
}

// ============================================================
// JSON Serialize Functions
// ============================================================

inline void serialize_CreateItemRequest_into(const CreateItemRequest& obj, std::string& json) {
    json.push_back('{');
    json.append("\"name\":");
    json.push_back('"');
    katana::serde::escape_json_string_into(obj.name, json);
    json.push_back('"');
    json.append(",\"quantity\":");
    {
        char buf[32];
        auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj.quantity);
        json.append(buf, static_cast<size_t>(ptr - buf));
    }
    json.append(",\"tag\":");
    if (obj.tag) {
        json.push_back('"');
        json.append(to_string(*obj.tag));
        json.push_back('"');
    } else {
        json.append("null");
    }
    json.append(",\"email\":");
    if (obj.email) {
        json.push_back('"');
        katana::serde::escape_json_string_into(*obj.email, json);
        json.push_back('"');
    } else {
        json.append("null");
    }
    json.push_back('}');
}

inline std::string serialize_CreateItemRequest(const CreateItemRequest& obj) {
    std::string json;
    size_t reserve_estimate = 154;
    reserve_estimate += obj.name.size();
    if (obj.email) reserve_estimate += obj.email->size();
    json.reserve(reserve_estimate);
    serialize_CreateItemRequest_into(obj, json);
    return json;
}

inline void serialize_CreateItemRequest_Name_t_into(const CreateItemRequest_Name_t& obj, std::string& json) {
    json.push_back('"');
    katana::serde::escape_json_string_into(obj, json);
    json.push_back('"');
}

inline std::string serialize_CreateItemRequest_Name_t(const CreateItemRequest_Name_t& obj) {
    std::string json;
    json.reserve(obj.size() + 16);
    serialize_CreateItemRequest_Name_t_into(obj, json);
    return json;
}

inline void serialize_CreateItemRequest_Quantity_t_into(const CreateItemRequest_Quantity_t& obj, std::string& json) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj);
    json.append(buf, static_cast<size_t>(ptr - buf));
}

inline std::string serialize_CreateItemRequest_Quantity_t(const CreateItemRequest_Quantity_t& obj) {
    std::string json;
    serialize_CreateItemRequest_Quantity_t_into(obj, json);
    return json;
}

inline void serialize_CreateItemRequest_Tag_t_into(const CreateItemRequest_Tag_t& obj, std::string& json) {
    auto str = to_string(obj);
    json.push_back('"');
    json.append(str);
    json.push_back('"');
}

inline std::string serialize_CreateItemRequest_Tag_t(const CreateItemRequest_Tag_t& obj) {
    std::string json;
    auto str = to_string(obj);
    json.reserve(str.size() + 2);
    serialize_CreateItemRequest_Tag_t_into(obj, json);
    return json;
}

inline void serialize_CreateItemRequest_Email_t_into(const CreateItemRequest_Email_t& obj, std::string& json) {
    json.push_back('"');
    katana::serde::escape_json_string_into(obj, json);
    json.push_back('"');
}

inline std::string serialize_CreateItemRequest_Email_t(const CreateItemRequest_Email_t& obj) {
    std::string json;
    json.reserve(obj.size() + 16);
    serialize_CreateItemRequest_Email_t_into(obj, json);
    return json;
}

inline void serialize_ItemResponse_into(const ItemResponse& obj, std::string& json) {
    json.push_back('{');
    json.append("\"id\":");
    {
        if (!obj.id) {
            json.append("null");
        } else {
            char buf[32];
            auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), *obj.id);
            json.append(buf, static_cast<size_t>(ptr - buf));
        }
    }
    json.append(",\"name\":");
    if (obj.name) {
        json.push_back('"');
        katana::serde::escape_json_string_into(*obj.name, json);
        json.push_back('"');
    } else {
        json.append("null");
    }
    json.append(",\"quantity\":");
    {
        if (!obj.quantity) {
            json.append("null");
        } else {
            char buf[32];
            auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), *obj.quantity);
            json.append(buf, static_cast<size_t>(ptr - buf));
        }
    }
    json.push_back('}');
}

inline std::string serialize_ItemResponse(const ItemResponse& obj) {
    std::string json;
    size_t reserve_estimate = 100;
    if (obj.name) reserve_estimate += obj.name->size();
    json.reserve(reserve_estimate);
    serialize_ItemResponse_into(obj, json);
    return json;
}

inline void serialize_ItemResponse_Id_t_into(const ItemResponse_Id_t& obj, std::string& json) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj);
    json.append(buf, static_cast<size_t>(ptr - buf));
}

inline std::string serialize_ItemResponse_Id_t(const ItemResponse_Id_t& obj) {
    std::string json;
    serialize_ItemResponse_Id_t_into(obj, json);
    return json;
}

inline void serialize_ItemResponse_Name_t_into(const ItemResponse_Name_t& obj, std::string& json) {
    json.push_back('"');
    katana::serde::escape_json_string_into(obj, json);
    json.push_back('"');
}

inline std::string serialize_ItemResponse_Name_t(const ItemResponse_Name_t& obj) {
    std::string json;
    json.reserve(obj.size() + 16);
    serialize_ItemResponse_Name_t_into(obj, json);
    return json;
}

inline void serialize_ItemResponse_Quantity_t_into(const ItemResponse_Quantity_t& obj, std::string& json) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj);
    json.append(buf, static_cast<size_t>(ptr - buf));
}

inline std::string serialize_ItemResponse_Quantity_t(const ItemResponse_Quantity_t& obj) {
    std::string json;
    serialize_ItemResponse_Quantity_t_into(obj, json);
    return json;
}

inline void serialize_schema_into(const schema& obj, std::string& json) {
    (void)obj;
    json.append("{}");
}

inline std::string serialize_schema(const schema& obj) {
    (void)obj;
    return std::string("{}");
}

inline void serialize_schema_1_into(const schema_1& obj, std::string& json) {
    (void)obj;
    json.append("{}");
}

inline std::string serialize_schema_1(const schema_1& obj) {
    (void)obj;
    return std::string("{}");
}

inline void serialize_list_items_param_limit_into(const list_items_param_limit& obj, std::string& json) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj);
    json.append(buf, static_cast<size_t>(ptr - buf));
}

inline std::string serialize_list_items_param_limit(const list_items_param_limit& obj) {
    std::string json;
    serialize_list_items_param_limit_into(obj, json);
    return json;
}

inline void serialize_list_items_response_into(const list_items_response& obj, std::string& json) {
    const auto& arr = obj;
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_list_items_response(const list_items_response& obj) {
    std::string json;
    json.reserve(obj.size() * 16 + 2);
    serialize_list_items_response_into(obj, json);
    return json;
}

inline void serialize_schema_2_into(const schema_2& obj, std::string& json) {
    (void)obj;
    json.append("{}");
}

inline std::string serialize_schema_2(const schema_2& obj) {
    (void)obj;
    return std::string("{}");
}

inline void serialize_get_item_param_id_into(const get_item_param_id& obj, std::string& json) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), obj);
    json.append(buf, static_cast<size_t>(ptr - buf));
}

inline std::string serialize_get_item_param_id(const get_item_param_id& obj) {
    std::string json;
    serialize_get_item_param_id_into(obj, json);
    return json;
}

inline void serialize_schema_3_into(const schema_3& obj, std::string& json) {
    (void)obj;
    json.append("{}");
}

inline std::string serialize_schema_3(const schema_3& obj) {
    (void)obj;
    return std::string("{}");
}

inline void serialize_echo_body_request_into(const echo_body_request& obj, std::string& json) {
    json.push_back('{');
    json.append("\"message\":");
    json.push_back('"');
    katana::serde::escape_json_string_into(obj.message, json);
    json.push_back('"');
    json.push_back('}');
}

inline std::string serialize_echo_body_request(const echo_body_request& obj) {
    std::string json;
    size_t reserve_estimate = 45;
    reserve_estimate += obj.message.size();
    json.reserve(reserve_estimate);
    serialize_echo_body_request_into(obj, json);
    return json;
}

inline void serialize_echo_body_request_Message_into(const echo_body_request_Message& obj, std::string& json) {
    json.push_back('"');
    katana::serde::escape_json_string_into(obj, json);
    json.push_back('"');
}

inline std::string serialize_echo_body_request_Message(const echo_body_request_Message& obj) {
    std::string json;
    json.reserve(obj.size() + 16);
    serialize_echo_body_request_Message_into(obj, json);
    return json;
}

inline void serialize_echo_body_response_into(const echo_body_response& obj, std::string& json) {
    json.push_back('{');
    json.append("\"echo\":");
    if (obj.echo) {
        json.push_back('"');
        katana::serde::escape_json_string_into(*obj.echo, json);
        json.push_back('"');
    } else {
        json.append("null");
    }
    json.push_back('}');
}

inline std::string serialize_echo_body_response(const echo_body_response& obj) {
    std::string json;
    size_t reserve_estimate = 42;
    if (obj.echo) reserve_estimate += obj.echo->size();
    json.reserve(reserve_estimate);
    serialize_echo_body_response_into(obj, json);
    return json;
}

inline void serialize_echo_body_response_Echo_into(const echo_body_response_Echo& obj, std::string& json) {
    json.push_back('"');
    katana::serde::escape_json_string_into(obj, json);
    json.push_back('"');
}

inline std::string serialize_echo_body_response_Echo(const echo_body_response_Echo& obj) {
    std::string json;
    json.reserve(obj.size() + 16);
    serialize_echo_body_response_Echo_into(obj, json);
    return json;
}

// ============================================================
// Array Parse Functions
// ============================================================

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest>> parse_CreateItemRequest_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<CreateItemRequest> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_CreateItemRequest(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest>> parse_CreateItemRequest_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Name_t>> parse_CreateItemRequest_Name_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<CreateItemRequest_Name_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_CreateItemRequest_Name_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Name_t>> parse_CreateItemRequest_Name_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Name_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Quantity_t>> parse_CreateItemRequest_Quantity_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<CreateItemRequest_Quantity_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_CreateItemRequest_Quantity_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Quantity_t>> parse_CreateItemRequest_Quantity_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Quantity_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Tag_t>> parse_CreateItemRequest_Tag_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<CreateItemRequest_Tag_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_CreateItemRequest_Tag_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Tag_t>> parse_CreateItemRequest_Tag_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Tag_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Email_t>> parse_CreateItemRequest_Email_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<CreateItemRequest_Email_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_CreateItemRequest_Email_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<CreateItemRequest_Email_t>> parse_CreateItemRequest_Email_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_CreateItemRequest_Email_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse>> parse_ItemResponse_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<ItemResponse> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_ItemResponse(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse>> parse_ItemResponse_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Id_t>> parse_ItemResponse_Id_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<ItemResponse_Id_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_ItemResponse_Id_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Id_t>> parse_ItemResponse_Id_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Id_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Name_t>> parse_ItemResponse_Name_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<ItemResponse_Name_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_ItemResponse_Name_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Name_t>> parse_ItemResponse_Name_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Name_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Quantity_t>> parse_ItemResponse_Quantity_t_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<ItemResponse_Quantity_t> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_ItemResponse_Quantity_t(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<ItemResponse_Quantity_t>> parse_ItemResponse_Quantity_t_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_ItemResponse_Quantity_t_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<schema>> parse_schema_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<schema> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_schema(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<schema>> parse_schema_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<schema_1>> parse_schema_1_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<schema_1> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_schema_1(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<schema_1>> parse_schema_1_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_1_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<list_items_param_limit>> parse_list_items_param_limit_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<list_items_param_limit> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_list_items_param_limit(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<list_items_param_limit>> parse_list_items_param_limit_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_list_items_param_limit_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<list_items_response>> parse_list_items_response_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<list_items_response> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_list_items_response(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<list_items_response>> parse_list_items_response_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_list_items_response_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<schema_2>> parse_schema_2_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<schema_2> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_schema_2(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<schema_2>> parse_schema_2_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_2_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<get_item_param_id>> parse_get_item_param_id_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<get_item_param_id> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_get_item_param_id(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<get_item_param_id>> parse_get_item_param_id_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_get_item_param_id_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<schema_3>> parse_schema_3_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<schema_3> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_schema_3(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<schema_3>> parse_schema_3_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_schema_3_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<echo_body_request>> parse_echo_body_request_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<echo_body_request> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_echo_body_request(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<echo_body_request>> parse_echo_body_request_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_request_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<echo_body_request_Message>> parse_echo_body_request_Message_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<echo_body_request_Message> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_echo_body_request_Message(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<echo_body_request_Message>> parse_echo_body_request_Message_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_request_Message_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<echo_body_response>> parse_echo_body_response_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<echo_body_response> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_echo_body_response(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<echo_body_response>> parse_echo_body_response_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_response_array(cur, arena);
}

[[nodiscard]] inline std::optional<std::vector<echo_body_response_Echo>> parse_echo_body_response_Echo_array(katana::serde::json_cursor& cur, monotonic_arena* arena) {
    if (!cur.try_array_start()) return std::nullopt;

    std::vector<echo_body_response_Echo> result;
    while (!cur.eof()) {
        cur.skip_ws();
        if (cur.try_array_end()) break;
        
        // Parse object at current cursor position
        auto obj = parse_echo_body_response_Echo(cur, arena);
        if (!obj) return std::nullopt;
        result.push_back(std::move(*obj));
        
        cur.try_comma();
    }
    return result;
}

[[nodiscard]] inline std::optional<std::vector<echo_body_response_Echo>> parse_echo_body_response_Echo_array(std::string_view json, monotonic_arena* arena) {
    katana::serde::json_cursor cur{json.data(), json.data() + json.size()};
    return parse_echo_body_response_Echo_array(cur, arena);
}

// ============================================================
// Array Serialize Functions
// ============================================================

inline void serialize_CreateItemRequest_array_into(const std::vector<CreateItemRequest>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_array(const std::vector<CreateItemRequest>& arr) {
    std::string json;
    json.reserve(arr.size() * 154 + 2);
    serialize_CreateItemRequest_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_array_into(const arena_vector<CreateItemRequest>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_array(const arena_vector<CreateItemRequest>& arr) {
    std::string json;
    json.reserve(arr.size() * 154 + 2);
    serialize_CreateItemRequest_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Name_t_array_into(const std::vector<CreateItemRequest_Name_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Name_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Name_t_array(const std::vector<CreateItemRequest_Name_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Name_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Name_t_array_into(const arena_vector<CreateItemRequest_Name_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Name_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Name_t_array(const arena_vector<CreateItemRequest_Name_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Name_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Quantity_t_array_into(const std::vector<CreateItemRequest_Quantity_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Quantity_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Quantity_t_array(const std::vector<CreateItemRequest_Quantity_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_CreateItemRequest_Quantity_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Quantity_t_array_into(const arena_vector<CreateItemRequest_Quantity_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Quantity_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Quantity_t_array(const arena_vector<CreateItemRequest_Quantity_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_CreateItemRequest_Quantity_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Tag_t_array_into(const std::vector<CreateItemRequest_Tag_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Tag_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Tag_t_array(const std::vector<CreateItemRequest_Tag_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Tag_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Tag_t_array_into(const arena_vector<CreateItemRequest_Tag_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Tag_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Tag_t_array(const arena_vector<CreateItemRequest_Tag_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Tag_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Email_t_array_into(const std::vector<CreateItemRequest_Email_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Email_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Email_t_array(const std::vector<CreateItemRequest_Email_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Email_t_array_into(arr, json);
    return json;
}

inline void serialize_CreateItemRequest_Email_t_array_into(const arena_vector<CreateItemRequest_Email_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_CreateItemRequest_Email_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_CreateItemRequest_Email_t_array(const arena_vector<CreateItemRequest_Email_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_CreateItemRequest_Email_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_array_into(const std::vector<ItemResponse>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_array(const std::vector<ItemResponse>& arr) {
    std::string json;
    json.reserve(arr.size() * 100 + 2);
    serialize_ItemResponse_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_array_into(const arena_vector<ItemResponse>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_array(const arena_vector<ItemResponse>& arr) {
    std::string json;
    json.reserve(arr.size() * 100 + 2);
    serialize_ItemResponse_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Id_t_array_into(const std::vector<ItemResponse_Id_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Id_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Id_t_array(const std::vector<ItemResponse_Id_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_ItemResponse_Id_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Id_t_array_into(const arena_vector<ItemResponse_Id_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Id_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Id_t_array(const arena_vector<ItemResponse_Id_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_ItemResponse_Id_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Name_t_array_into(const std::vector<ItemResponse_Name_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Name_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Name_t_array(const std::vector<ItemResponse_Name_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_ItemResponse_Name_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Name_t_array_into(const arena_vector<ItemResponse_Name_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Name_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Name_t_array(const arena_vector<ItemResponse_Name_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_ItemResponse_Name_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Quantity_t_array_into(const std::vector<ItemResponse_Quantity_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Quantity_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Quantity_t_array(const std::vector<ItemResponse_Quantity_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_ItemResponse_Quantity_t_array_into(arr, json);
    return json;
}

inline void serialize_ItemResponse_Quantity_t_array_into(const arena_vector<ItemResponse_Quantity_t>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_ItemResponse_Quantity_t_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_ItemResponse_Quantity_t_array(const arena_vector<ItemResponse_Quantity_t>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_ItemResponse_Quantity_t_array_into(arr, json);
    return json;
}

inline void serialize_schema_array_into(const std::vector<schema>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_array(const std::vector<schema>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_array_into(arr, json);
    return json;
}

inline void serialize_schema_array_into(const arena_vector<schema>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_array(const arena_vector<schema>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_array_into(arr, json);
    return json;
}

inline void serialize_schema_1_array_into(const std::vector<schema_1>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_1_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_1_array(const std::vector<schema_1>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_1_array_into(arr, json);
    return json;
}

inline void serialize_schema_1_array_into(const arena_vector<schema_1>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_1_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_1_array(const arena_vector<schema_1>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_1_array_into(arr, json);
    return json;
}

inline void serialize_list_items_param_limit_array_into(const std::vector<list_items_param_limit>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_list_items_param_limit_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_list_items_param_limit_array(const std::vector<list_items_param_limit>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_list_items_param_limit_array_into(arr, json);
    return json;
}

inline void serialize_list_items_param_limit_array_into(const arena_vector<list_items_param_limit>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_list_items_param_limit_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_list_items_param_limit_array(const arena_vector<list_items_param_limit>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_list_items_param_limit_array_into(arr, json);
    return json;
}

inline void serialize_list_items_response_array_into(const std::vector<list_items_response>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_list_items_response_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_list_items_response_array(const std::vector<list_items_response>& arr) {
    std::string json;
    json.reserve(arr.size() * 402 + 2);
    serialize_list_items_response_array_into(arr, json);
    return json;
}

inline void serialize_list_items_response_array_into(const arena_vector<list_items_response>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_list_items_response_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_list_items_response_array(const arena_vector<list_items_response>& arr) {
    std::string json;
    json.reserve(arr.size() * 402 + 2);
    serialize_list_items_response_array_into(arr, json);
    return json;
}

inline void serialize_schema_2_array_into(const std::vector<schema_2>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_2_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_2_array(const std::vector<schema_2>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_2_array_into(arr, json);
    return json;
}

inline void serialize_schema_2_array_into(const arena_vector<schema_2>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_2_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_2_array(const arena_vector<schema_2>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_2_array_into(arr, json);
    return json;
}

inline void serialize_get_item_param_id_array_into(const std::vector<get_item_param_id>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_get_item_param_id_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_get_item_param_id_array(const std::vector<get_item_param_id>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_get_item_param_id_array_into(arr, json);
    return json;
}

inline void serialize_get_item_param_id_array_into(const arena_vector<get_item_param_id>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_get_item_param_id_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_get_item_param_id_array(const arena_vector<get_item_param_id>& arr) {
    std::string json;
    json.reserve(arr.size() * 20 + 2);
    serialize_get_item_param_id_array_into(arr, json);
    return json;
}

inline void serialize_schema_3_array_into(const std::vector<schema_3>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_3_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_3_array(const std::vector<schema_3>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_3_array_into(arr, json);
    return json;
}

inline void serialize_schema_3_array_into(const arena_vector<schema_3>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_schema_3_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_schema_3_array(const arena_vector<schema_3>& arr) {
    std::string json;
    json.reserve(arr.size() * 2 + 2);
    serialize_schema_3_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_request_array_into(const std::vector<echo_body_request>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_request_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_request_array(const std::vector<echo_body_request>& arr) {
    std::string json;
    json.reserve(arr.size() * 45 + 2);
    serialize_echo_body_request_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_request_array_into(const arena_vector<echo_body_request>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_request_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_request_array(const arena_vector<echo_body_request>& arr) {
    std::string json;
    json.reserve(arr.size() * 45 + 2);
    serialize_echo_body_request_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_request_Message_array_into(const std::vector<echo_body_request_Message>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_request_Message_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_request_Message_array(const std::vector<echo_body_request_Message>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_echo_body_request_Message_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_request_Message_array_into(const arena_vector<echo_body_request_Message>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_request_Message_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_request_Message_array(const arena_vector<echo_body_request_Message>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_echo_body_request_Message_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_response_array_into(const std::vector<echo_body_response>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_response_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_response_array(const std::vector<echo_body_response>& arr) {
    std::string json;
    json.reserve(arr.size() * 42 + 2);
    serialize_echo_body_response_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_response_array_into(const arena_vector<echo_body_response>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_response_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_response_array(const arena_vector<echo_body_response>& arr) {
    std::string json;
    json.reserve(arr.size() * 42 + 2);
    serialize_echo_body_response_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_response_Echo_array_into(const std::vector<echo_body_response_Echo>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_response_Echo_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_response_Echo_array(const std::vector<echo_body_response_Echo>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_echo_body_response_Echo_array_into(arr, json);
    return json;
}

inline void serialize_echo_body_response_Echo_array_into(const arena_vector<echo_body_response_Echo>& arr, std::string& json) {
    json.push_back('[');
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) json.push_back(',');
        serialize_echo_body_response_Echo_into(arr[i], json);
    }
    json.push_back(']');
}

inline std::string serialize_echo_body_response_Echo_array(const arena_vector<echo_body_response_Echo>& arr) {
    std::string json;
    json.reserve(arr.size() * 32 + 2);
    serialize_echo_body_response_Echo_array_into(arr, json);
    return json;
}

