#pragma once
#include <cstdint>
#include <cstddef>

// ===========================================================================
// Hash primitives used by the game's std::unordered_map / std::unordered_set.
//
// The Warhorse hash containers ARE stock MSVC std::unordered_map/unordered_set
// (0x40 _Hash header; verified in IDA + against the STL source). The replica
// classes that used to live here (C_HashMap/C_Set) have been removed -- callers
// now use the real std:: types directly. What remains are the hash functions the
// engine's keys hash with, for the custom (transparent) hashers that std needs:
//
//   FNV-1a 64  (sub_1804BF50C) -- MSVC std::hash's algorithm for trivially-copyable
//              keys; also the explicit hasher for struct keys (WUID, EntityGUID).
//   FNV-1  32  (sub_1802540B4) -- for null-terminated strings (e.g. info labels).
//   hash_combine (boost pattern, 0x1815d4042) -- folds field hashes for composite keys.
// ===========================================================================

namespace wh::shared {

// FNV-1a 64-bit over `len` raw bytes. (sub_1804BF50C)
inline uint64_t fnv1a(const void* data, size_t len) {
    uint64_t h = 0xCBF29CE484222325ULL;
    auto p = static_cast<const uint8_t*>(data);
    for (size_t i = 0; i < len; ++i)
        h = (h ^ p[i]) * 0x100000001B3ULL;
    return h;
}

// FNV-1 32-bit over a null-terminated string. (sub_1802540B4)
inline uint32_t fnv1_32(const char* str) {
    uint32_t h = 0x811C9DC5u;
    while (*str)
        h = (h * 0x01000193u) ^ static_cast<uint8_t>(*str++);
    return h;
}

// boost::hash_combine (0x1815d4042-0x1815d406d).
inline uint64_t hash_combine(uint64_t seed, uint64_t value) {
    seed ^= value + 0x9E3779B9ULL + (seed << 6) + (seed >> 2);
    return seed;
}

// Default hasher (FNV-1a over sizeof(K) raw bytes) for struct keys whose std::hash
// the project doesn't specialize (e.g. WUID, EntityGUID). Pass as the Hash arg:
//   std::unordered_map<WUID, V, wh::shared::S_DefaultHash<WUID>>
// Matches MSVC std::hash for trivially-copyable K.
template<typename K>
struct S_DefaultHash {
    uint64_t operator()(const K& key) const { return fnv1a(&key, sizeof(K)); }
};

}  // namespace wh::shared
