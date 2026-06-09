#pragma once

#include <cstdint>
#include "rpgmodule/I_POI.h"

// -----------------------------------------------
// _reference_target<int> — CryEngine refcount base for _smart_ptr
// -----------------------------------------------
// Binary vtable (4 slots, from C_POI primary at 0x1826d3e10)

class _reference_target_int {
public:
    virtual void _ref_vf0() {}      // [0] sub_18118ED04
    virtual void _ref_vf1() {}      // [1] sub_1806FF5A0
    virtual void _ref_vf2() {}      // [2] sub_1806F86F0  AddRef
    virtual void _ref_vf3() {}      // [3] sub_1806F86F0  Release

    int32_t     m_nRefCount;        // +0x08
    char        _pad0C[0x4];        // +0x0C
};
static_assert(sizeof(_reference_target_int) == 0x10);

// -----------------------------------------------
// C_POI — concrete POI implementation
// -----------------------------------------------
// RTTI: .?AVC_POI@rpgmodule@wh@@
// Inherits:
//   [+0x00] _reference_target<int>  (CryEngine refcount for _smart_ptr)
//   [+0x10] I_POI                   (POI interface)
//
// Primary vtable at 0x1826d3e10 (4 slots)
// I_POI vtable at 0x1826d3e38 (35+ slots)
//
// Used in: _smart_ptr<C_POI>, PodArray<_smart_ptr<C_POI>>
//
// Member offsets below are relative to C_POI base (= I_POI* - 0x10).
// The I_POI vtable methods access these as (this + offset) where
// this = I_POI* = C_POI + 0x10, so e.g. GetEntityId reads this+0x78 = C_POI+0x88.

namespace wh::rpgmodule {

class C_POI
    : public _reference_target_int   // +0x00  (4 slots, refcount at +0x08)
    , public I_POI                   // +0x10  (35+ slots, POI interface)
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_POI;
    // --- Members (offsets relative to C_POI base) ---
    uint64_t    m_unk18;            // +0x18  (I_POI+0x08)
    uint64_t    m_unk20;            // +0x20  (I_POI+0x10)
    uint64_t    m_locationId;       // +0x28  (I_POI+0x18)
    uint64_t    m_unk30;            // +0x30  (I_POI+0x20)
    char*       m_szLayerName;      // +0x38  (I_POI+0x28)
    uint64_t    m_unk40;            // +0x40  (I_POI+0x30)
    int32_t     m_nState;           // +0x48  (I_POI+0x38) current state (-1 = inherit)
    char        _pad4C[0x4];        // +0x4C
    uint64_t    m_unk50;            // +0x50  (I_POI+0x40)
    uint64_t    m_unk58;            // +0x58  (I_POI+0x48)
    void*       m_pShape;           // +0x60  (I_POI+0x50)
    uint64_t    m_unk68;            // +0x68  (I_POI+0x58)
    uint64_t    m_unk70;            // +0x70  (I_POI+0x60)
    uint64_t    m_unk78;            // +0x78  (I_POI+0x68)
    uint32_t    m_nInitialState;    // +0x80  (I_POI+0x70)
    char        _pad84[0x4];        // +0x84
    uint32_t    m_nEntityId;        // +0x88  (I_POI+0x78) read by GetEntityId
    uint16_t    m_nFlags;           // +0x8C  (I_POI+0x7C) read by GetFlags/HasFlag
    char        _pad8E[0x2];        // +0x8E

    bool IsFastTravel() const   { return (m_nFlags & 0x02) != 0; }
    bool IsDiscoverable() const { return (m_nFlags & 0x01) != 0; }
    bool IsProcedural() const   { return (m_nFlags & 0x04) != 0; }
    bool IsBed() const          { return (m_nFlags & 0x08) != 0; }
    bool IsUnloaded() const     { return (m_nFlags & 0x20) != 0; }
};

}  // namespace wh::rpgmodule
