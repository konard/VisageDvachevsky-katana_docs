#include "katana/core/media_type_registry.hpp"

#include <gtest/gtest.h>

using namespace katana;

// ============================================================
// Registry lookup tests
// ============================================================

TEST(MediaTypeRegistry, FindJsonReturnsIndex) {
    auto idx = media_type_registry::find("application/json");
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(*idx, 0u);
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].mime_type, "application/json");
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].codec, codec_id::json);
}

TEST(MediaTypeRegistry, FindCborReturnsIndex) {
    auto idx = media_type_registry::find("application/cbor");
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].codec, codec_id::cbor);
}

TEST(MediaTypeRegistry, FindMsgpackReturnsIndex) {
    auto idx = media_type_registry::find("application/msgpack");
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].codec, codec_id::msgpack);
}

TEST(MediaTypeRegistry, FindXMsgpackReturnsIndex) {
    auto idx = media_type_registry::find("application/x-msgpack");
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].codec, codec_id::msgpack);
}

TEST(MediaTypeRegistry, FindUnknownReturnsNullopt) {
    auto idx = media_type_registry::find("text/html");
    EXPECT_FALSE(idx.has_value());
}

TEST(MediaTypeRegistry, FindIcaseMatchesJson) {
    auto idx = media_type_registry::find_icase("Application/JSON");
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(media_type_registry::builtin_entries[*idx].codec, codec_id::json);
}

TEST(MediaTypeRegistry, FindIcaseUnknown) {
    auto idx = media_type_registry::find_icase("TEXT/XML");
    EXPECT_FALSE(idx.has_value());
}

// ============================================================
// Registration status tests
// ============================================================

TEST(MediaTypeRegistry, IsRegisteredJson) {
    EXPECT_TRUE(media_type_registry::is_registered("application/json"));
}

TEST(MediaTypeRegistry, IsRegisteredCbor) {
    EXPECT_TRUE(media_type_registry::is_registered("application/cbor"));
}

TEST(MediaTypeRegistry, IsRegisteredUnknown) {
    EXPECT_FALSE(media_type_registry::is_registered("text/plain"));
}

TEST(MediaTypeRegistry, IsSupportedJson) {
    EXPECT_TRUE(media_type_registry::is_supported("application/json"));
}

TEST(MediaTypeRegistry, IsSupportedCborIsStub) {
    // CBOR is registered but only as a stub
    EXPECT_FALSE(media_type_registry::is_supported("application/cbor"));
}

TEST(MediaTypeRegistry, IsSupportedMsgpackIsStub) {
    EXPECT_FALSE(media_type_registry::is_supported("application/msgpack"));
}

// ============================================================
// Codec resolution tests
// ============================================================

TEST(MediaTypeRegistry, CodecForJson) {
    auto c = media_type_registry::codec_for("application/json");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::json);
}

TEST(MediaTypeRegistry, CodecForCbor) {
    auto c = media_type_registry::codec_for("application/cbor");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::cbor);
}

TEST(MediaTypeRegistry, CodecForUnknown) {
    auto c = media_type_registry::codec_for("text/plain");
    EXPECT_FALSE(c.has_value());
}

// ============================================================
// Entries span tests
// ============================================================

TEST(MediaTypeRegistry, EntriesSpanSize) {
    auto entries = media_type_registry::entries();
    EXPECT_EQ(entries.size(), media_type_registry::builtin_count);
    EXPECT_GE(entries.size(), 4u);
}

TEST(MediaTypeRegistry, SupportedEntriesOnlyJson) {
    auto supported = media_type_registry::supported_entries();
    EXPECT_EQ(supported.size(), 1u);
    EXPECT_EQ(supported[0].mime_type, "application/json");
}

// ============================================================
// Codec capability tests
// ============================================================

TEST(CodecCaps, BitwiseOr) {
    auto caps = codec_caps::decode | codec_caps::encode;
    EXPECT_EQ(caps, codec_caps::full);
}

TEST(CodecCaps, BitwiseAnd) {
    auto caps = codec_caps::full & codec_caps::decode;
    EXPECT_EQ(caps, codec_caps::decode);
}

TEST(CodecCaps, HasCap) {
    EXPECT_TRUE(has_cap(codec_caps::full, codec_caps::decode));
    EXPECT_TRUE(has_cap(codec_caps::full, codec_caps::encode));
    EXPECT_FALSE(has_cap(codec_caps::decode, codec_caps::encode));
    EXPECT_FALSE(has_cap(codec_caps::none, codec_caps::decode));
}

// ============================================================
// Request codec resolution tests
// ============================================================

TEST(ResolveRequestCodec, JsonContentType) {
    auto c = resolve_request_codec("application/json");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::json);
}

TEST(ResolveRequestCodec, JsonWithCharset) {
    auto c = resolve_request_codec("application/json; charset=utf-8");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::json);
}

TEST(ResolveRequestCodec, CborIsStub) {
    auto c = resolve_request_codec("application/cbor");
    EXPECT_FALSE(c.has_value()); // stub codecs should not resolve
}

TEST(ResolveRequestCodec, UnknownType) {
    auto c = resolve_request_codec("text/xml");
    EXPECT_FALSE(c.has_value());
}

TEST(ResolveRequestCodec, CaseInsensitive) {
    auto c = resolve_request_codec("Application/JSON");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::json);
}

// ============================================================
// Response codec resolution tests
// ============================================================

TEST(ResolveResponseCodec, JsonMimeType) {
    auto c = resolve_response_codec("application/json");
    ASSERT_TRUE(c.has_value());
    EXPECT_EQ(*c, codec_id::json);
}

TEST(ResolveResponseCodec, CborIsStub) {
    auto c = resolve_response_codec("application/cbor");
    EXPECT_FALSE(c.has_value());
}

TEST(ResolveResponseCodec, UnknownType) {
    auto c = resolve_response_codec("image/png");
    EXPECT_FALSE(c.has_value());
}

// ============================================================
// Conversion helper tests
// ============================================================

TEST(ToContentTypeInfo, ConvertsEntry) {
    auto info = to_content_type_info(media_type_registry::builtin_entries[0]);
    EXPECT_EQ(info.mime_type, "application/json");
}

// ============================================================
// Constexpr verification
// ============================================================

TEST(MediaTypeRegistry, ConstexprFind) {
    // Verify that find() works at compile time
    static_assert(media_type_registry::find("application/json").has_value());
    static_assert(!media_type_registry::find("text/html").has_value());
    static_assert(media_type_registry::is_registered("application/json"));
    static_assert(media_type_registry::is_supported("application/json"));
    static_assert(!media_type_registry::is_supported("application/cbor"));
    static_assert(media_type_registry::codec_for("application/json") == codec_id::json);
}
