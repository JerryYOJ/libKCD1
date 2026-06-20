#pragma once

#include <cstddef>
#include <functional>
// CryStringT<char> comes from the PCH prelude.

// ===========================================================================
// std::hash<CryStringT<char>>  -  enables CryStringT<char> as an associative-
// container key in REPLICA headers.
// ===========================================================================
// Several engine classes key std::unordered_map / std::unordered_set on a
// CryStringT<char> (the "wh::framework::StringHash" handle, which is byte-
// identical to CryStringT<char>). MSVC's std::unordered_map<Key,...> requires a
// usable std::hash<Key>; the default primary template disables itself for
// CryStringT. Our headers only MODEL layout (sizeof is 0x40 regardless of Key),
// so this hash is never actually called at runtime -- but it must exist and be
// callable for the member declarations to compile. equal_to<CryStringT<char>>
// already works via CryStringT::operator==, so only hash is specialized here.
// ===========================================================================

template <>
struct std::hash<CryStringT<char>> {
    std::size_t operator()(const CryStringT<char>& s) const noexcept {
        // FNV-1a over the pooled char data (never invoked; layout modelling only).
        std::size_t h = 1469598103934665603ull;
        for (const char* p = s.c_str(); p && *p; ++p) {
            h ^= static_cast<unsigned char>(*p);
            h *= 1099511628211ull;
        }
        return h;
    }
};
