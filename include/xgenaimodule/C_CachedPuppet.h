#pragma once

#include <cstdint>
#include "I_AIPuppet.h"

// ===========================================================================
// wh::xgenaimodule::C_CachedPuppet : I_AIPuppet
// ===========================================================================
// RTTI: .?AVC_CachedPuppet@xgenaimodule@wh@@
// vtable: 0x1821AD680 (24 slots). Overrides ONLY slot 0 (its own deleting dtor,
//         sub_18167DD24); every other slot is inherited verbatim from I_AIPuppet
//         (slots 1..14, 16..20 are still _purecall) -> C_CachedPuppet is ABSTRACT.
//
// Ctor:  sub_1804509AC(this)
//          this+0x20 = 0                        (m_cacheToken: cache invalid)
//          this+0x00 = &C_CachedPuppet::vftable
//          this+0x28 = sub_18028D060() + 0xC    (interned-name handle: data ptr
//                                                past the 12-byte pool header;
//                                                starts as the shared empty string)
// Dtor body: sub_18044FAC8(this) — releases the interned name via
//          wh::framework::StringHashCleanup(*(this+0x28) - 0xC) (refcount at
//          handle-0xC), unhooks from the allocation tracker, resets vtable.
//
// Adds the *transform cache* used by C_AIPuppet's world-query slots: the cached
// world position and the cached forward (look) direction are filled lazily and
// validated against the global frame token dword_1829C8B94 (slots 5/6 in
// C_AIPuppet refresh m_cachedPos / m_cachedForward then stamp m_cacheToken).
//
// size 0x30.
// ===========================================================================

namespace wh::xgenaimodule {

class C_CachedPuppet : public I_AIPuppet {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CachedPuppet;
    // Overrides only the destructor (sub_18167DD24 -> sub_18044FAC8).
    ~C_CachedPuppet() override;

    // --- fields (verified from ctor sub_1804509AC + cache writers sub_18033C404 /
    //     sub_1802866A0 + dtor body sub_18044FAC8) ---
    Vec3        m_cachedPos;     // +0x08  cached world position (slot 5 result)
    Vec3        m_cachedForward; // +0x14  cached forward (look) DIRECTION unit vector
                                 //        = column 1 of the entity's orthonormalized rotation
                                 //        matrix (M[0][1],M[1][1],M[2][1]); CryEngine forward
                                 //        dir. Refreshed alongside m_cachedPos. (slot 6 result)
                                 //        VERIFIED src = rot-matrix col1 @0x18033c50c, written
                                 //        @0x18033c4ba/0x18033c4c2 (was mislabeled "m_cachedAux").
    int32_t     m_cacheToken;    // +0x20  last frame the cache was refreshed; compared
                                 //        against global dword_1829C8B94, ctor sets 0 (sub_1804509AC)
    char        _pad24[4];     // +0x24  (align +0x28 to 8)
    const char* m_name;        // +0x28  interned/refcounted name handle (Warhorse
                               //        StringHash: pooled char data; refcount at
                               //        m_name-0xC). Ctor inits to the empty string.
};
static_assert(sizeof(C_CachedPuppet) == 0x30);

}  // namespace wh::xgenaimodule
