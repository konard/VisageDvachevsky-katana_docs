#pragma once

// Unified content negotiation layer.
//
// Stage 3 refactor: content_type_info and media type extraction are now
// defined once in http_utils.hpp.  This header re-exports them into
// katana::http for backward compatibility and provides the middleware
// factory that validates Content-Type (415) and Accept (406).

#include "http.hpp"
#include "http_utils.hpp"
#include "media_type_registry.hpp"
#include "problem.hpp"
#include "result.hpp"
#include "router.hpp"

#include <span>
#include <string_view>

namespace katana::http {

// Re-export the canonical content_type_info from http_utils
// so that existing code using katana::http::content_type_info keeps compiling.
using katana::http_utils::content_type_info;

// Delegate media type extraction to the single implementation in http_utils.
// Strips parameters (e.g., "; charset=utf-8") and trims whitespace.
[[nodiscard]] inline std::string_view
extract_media_type(std::string_view content_type) noexcept {
    return http_utils::detail::media_type_token(content_type);
}

// Check if request Content-Type is acceptable for this route.
// Delegates to http_utils::find_content_type for consistent case-insensitive matching.
[[nodiscard]] inline bool
validate_content_type(const request& req,
                      std::span<const content_type_info> accepted_types) noexcept {
    if (accepted_types.empty()) {
        return true;
    }
    auto ct = req.headers.get(field::content_type);
    return http_utils::find_content_type(ct, accepted_types).has_value();
}

// Check if response can satisfy the Accept header.
// Delegates to http_utils::negotiate_response_type — if it can pick a type, the
// Accept header is satisfiable.
[[nodiscard]] inline bool
validate_accept(const request& req,
                std::span<const content_type_info> available_types) noexcept {
    if (available_types.empty()) {
        return true;
    }
    return http_utils::negotiate_response_type(req, available_types).has_value();
}

// Middleware factory for content negotiation (415/406).
inline middleware_fn
make_content_negotiation_middleware(std::span<const content_type_info> consumes,
                                    std::span<const content_type_info> produces) {
    return [consumes, produces](const request& req, request_context& ctx, response& out,
                                next_fn next) -> result<void> {
        (void)ctx;
        if (!validate_content_type(req, consumes)) {
            respond::into(out).problem(problem_details::unsupported_media_type());
            return {};
        }
        if (!validate_accept(req, produces)) {
            respond::into(out).problem(problem_details::not_acceptable());
            return {};
        }
        return next(out);
    };
}

} // namespace katana::http
