#pragma once

#include <cstdint>
#include <memory>

// -----------------------------------------------
// C_CompassMark — map marker / checkpoint / POI mark
// -----------------------------------------------
// RTTI: .?AVC_CompassMark@guimodule@wh@@
// Inherits: I_AreaTracker (wh::xgenaimodule)
// Created via std::make_shared (0x68 alloc = 0x10 refcount header + 0x58 object)
// Constructor: sub_181123C24
// Binary vtable at 0x1822e6b50 (4 slots primary + more)
// Size: 0x58 (object portion, excluding shared_ptr control block)

namespace wh::guimodule {

class C_CompassMark {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CompassMark;
    virtual void _vf0() {}   // [0] sub_18110F6B0
    virtual void _vf1() {}   // [1] sub_18110F6BC
    virtual void _vf2() {}   // [2] nop
    virtual void _vf3() {}   // [3] sub_18110D4F0

    uint64_t    m_unk08;        // +0x08
    uint8_t     m_flags;        // +0x10
    char        _pad11[0x7];    // +0x11
    uint64_t    m_unk18;        // +0x18
    uint64_t    m_unk20;        // +0x20
    uint64_t    m_entityId;     // +0x28
    float       m_fPosX;        // +0x30
    float       m_fPosY;        // +0x34
    float       m_fPosZ;        // +0x38
    uint32_t    m_unk3C;        // +0x3C
    uint64_t    m_unk40;        // +0x40
    uint64_t    m_unk48;        // +0x48
    int32_t     m_nMarkId;      // +0x50  auto-increment ID
    uint8_t     m_unk54;        // +0x54
    char        _pad55[0x3];    // +0x55
};
static_assert(sizeof(C_CompassMark) == 0x58);

}  // namespace wh::guimodule
