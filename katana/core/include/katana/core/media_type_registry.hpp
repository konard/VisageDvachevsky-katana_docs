#pragma once

#include "http_utils.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <string_view>

namespace katana {

// Forward declarations
struct monotonic_arena;

/// Codec identifier — lightweight enum for compile-time codec selection.
enum class codec_id : uint8_t {
    json = 0,
    cbor = 1,
    msgpack = 2,
    // Reserve space for user-defined codecs
    custom_start = 64,
};

/// Codec capability flags — what a codec can do.
enum class codec_caps : uint8_t {
    none = 0,
    decode = 1,      // Can deserialize (parse request bodies)
    encode = 2,      // Can serialize (write response bodies)
    full = 3,        // Both decode and encode
    stub = 4,        // Registered but not yet implemented (contract surface only)
};

[[nodiscard]] constexpr codec_caps operator|(codec_caps a, codec_caps b) noexcept {
    return static_cast<codec_caps>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

[[nodiscard]] constexpr codec_caps operator&(codec_caps a, codec_caps b) noexcept {
    return static_cast<codec_caps>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

[[nodiscard]] constexpr bool has_cap(codec_caps caps, codec_caps flag) noexcept {
    return (caps & flag) == flag;
}

/// A single entry in the media type registry: maps a MIME type to a codec.
struct media_type_entry {
    std::string_view mime_type;   // e.g., "application/json"
    codec_id codec;               // Which codec handles this type
    codec_caps caps;              // What the codec can do
};

/// Compile-time media type registry.
///
/// Maps MIME types to codec identifiers. The registry is a constexpr-friendly
/// span of entries, enabling zero-cost lookups in generated code.
///
/// Usage (runtime):
///   auto idx = registry::find("application/json");
///   if (idx) { auto& entry = registry::entries()[*idx]; ... }
///
/// Usage (codegen):
///   The code generator emits constexpr arrays referencing registry entries,
///   so generated routers use the same lookup path as hand-written code.
class media_type_registry {
public:
    /// Built-in registry entries (JSON production-ready, CBOR/MessagePack stubs).
    static constexpr media_type_entry builtin_entries[] = {
        {"application/json", codec_id::json, codec_caps::full},
        {"application/cbor", codec_id::cbor, codec_caps::stub},
        {"application/msgpack", codec_id::msgpack, codec_caps::stub},
        {"application/x-msgpack", codec_id::msgpack, codec_caps::stub},
    };

    static constexpr size_t builtin_count =
        sizeof(builtin_entries) / sizeof(builtin_entries[0]);

    /// Find a media type in the built-in registry (case-sensitive exact match).
    /// Returns the index into builtin_entries, or nullopt if not found.
    [[nodiscard]] static constexpr std::optional<size_t>
    find(std::string_view mime_type) noexcept {
        for (size_t i = 0; i < builtin_count; ++i) {
            if (builtin_entries[i].mime_type == mime_type) {
                return i;
            }
        }
        return std::nullopt;
    }

    /// Find a media type using case-insensitive comparison.
    [[nodiscard]] static std::optional<size_t>
    find_icase(std::string_view mime_type) noexcept {
        for (size_t i = 0; i < builtin_count; ++i) {
            if (http_utils::detail::ascii_iequals(builtin_entries[i].mime_type, mime_type)) {
                return i;
            }
        }
        return std::nullopt;
    }

    /// Check if a media type is registered (any capability).
    [[nodiscard]] static constexpr bool
    is_registered(std::string_view mime_type) noexcept {
        return find(mime_type).has_value();
    }

    /// Check if a media type has full (non-stub) codec support.
    [[nodiscard]] static constexpr bool
    is_supported(std::string_view mime_type) noexcept {
        auto idx = find(mime_type);
        if (!idx) return false;
        return !has_cap(builtin_entries[*idx].caps, codec_caps::stub);
    }

    /// Get the codec_id for a given media type, or nullopt if not registered.
    [[nodiscard]] static constexpr std::optional<codec_id>
    codec_for(std::string_view mime_type) noexcept {
        auto idx = find(mime_type);
        if (!idx) return std::nullopt;
        return builtin_entries[*idx].codec;
    }

    /// Get all entries as a span (for iteration / content negotiation).
    [[nodiscard]] static constexpr std::span<const media_type_entry>
    entries() noexcept {
        return {builtin_entries, builtin_count};
    }

    /// Get only fully-supported (non-stub) entries as content_type_info span.
    /// Useful for generating default consumes/produces arrays.
    [[nodiscard]] static constexpr std::span<const media_type_entry>
    supported_entries() noexcept {
        // Currently only JSON is non-stub (index 0).
        // When CBOR/MessagePack are promoted, update this.
        return {builtin_entries, 1};
    }
};

/// Convert a media_type_entry to an http_utils::content_type_info.
/// This bridges the registry with existing negotiation functions.
[[nodiscard]] constexpr http_utils::content_type_info
to_content_type_info(const media_type_entry& entry) noexcept {
    return {entry.mime_type};
}

/// Negotiate the response content type from the Accept header,
/// considering only codecs that are fully supported (non-stub).
///
/// This is the unified replacement for the duplicated logic in
/// content_negotiation.hpp::validate_accept() and
/// http_utils.hpp::negotiate_response_type().
///
/// When the route produces a single media type (common case),
/// call negotiate_response_type() from http_utils.hpp directly —
/// it already has optimized fast paths.
[[nodiscard]] inline std::optional<std::string_view>
negotiate_with_registry(const http::request& req,
                        std::span<const http_utils::content_type_info> produces) noexcept {
    return http_utils::negotiate_response_type(req, produces);
}

/// Select the codec_id for a validated Content-Type header value.
/// Returns nullopt if the media type is unknown or only a stub.
[[nodiscard]] inline std::optional<codec_id>
resolve_request_codec(std::string_view content_type_header) noexcept {
    auto media = http_utils::detail::media_type_token(content_type_header);
    auto idx = media_type_registry::find_icase(media);
    if (!idx) return std::nullopt;
    const auto& entry = media_type_registry::builtin_entries[*idx];
    if (has_cap(entry.caps, codec_caps::stub)) return std::nullopt;
    if (!has_cap(entry.caps, codec_caps::decode)) return std::nullopt;
    return entry.codec;
}

/// Select the codec_id for a response media type.
/// Returns nullopt if the media type is unknown or only a stub.
[[nodiscard]] inline std::optional<codec_id>
resolve_response_codec(std::string_view mime_type) noexcept {
    auto idx = media_type_registry::find(mime_type);
    if (!idx) return std::nullopt;
    const auto& entry = media_type_registry::builtin_entries[*idx];
    if (has_cap(entry.caps, codec_caps::stub)) return std::nullopt;
    if (!has_cap(entry.caps, codec_caps::encode)) return std::nullopt;
    return entry.codec;
}

} // namespace katana
