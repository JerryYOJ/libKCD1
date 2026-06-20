#pragma once

#include <cstdint>
// CryStringT<char> comes from the PCH prelude.

// ===========================================================================
// wh::xgenaimodule::S_VariableReference  -  a named reference into the AI variable system.
// ===========================================================================
// RTTI: .?AVS_VariableReference@... (TD 0x182b37ff0); derives S_ConstVariableReference (TD 0x182adbb20)
// at +0x00 (same 0x60 layout, overriding vtable slots 0/3/7/8). vtable 0x1821A2E68 (9 slots; base
// vtable 0x1821A4DF0). size 0x60. Embedded value (e.g. C_SmartArea+0x288). ctor sub_180207B44; the BT
// variable nodes (Expression/VarOperation/StopFastTravel) stage these from their context. NOT
// interfuscated. (Modeled flat as S_VariableReference; the S_ConstVariableReference base is layout-
// identical and differs only in 4 overridden vtable slots.)
// ===========================================================================

namespace wh::xgenaimodule {

struct S_VariableReference {
    virtual ~S_VariableReference();   // [0] sub_180206BFC (S_ConstVariableReference [0] = sub_180206BC4)
    virtual void _vf1();              // [1] sub_1803B1B18
    virtual void _vf2();              // [2] sub_1803B1C78
    virtual void _vf3();              // [3] sub_1803B1CF0 (override)
    virtual void _vf4();              // [4] sub_1803B1C18
    virtual void _vf5();              // [5] sub_1803B1BA0
    virtual void _vf6();              // [6] sub_1803B1A80
    virtual void _vf7();              // [7] sub_180249910 (override)
    virtual void _vf8();              // [8] sub_1802CB0EC (override)

    uint16_t          m_unk08;        // +0x08
    uint8_t           m_unk0A;        // +0x0A
    uint8_t           _pad0B[5];      // +0x0B
    CryStringT<char>  m_name0;        // +0x10  (empty in ctor)
    CryStringT<char>  m_name1;        // +0x18  (empty in ctor)
    uint64_t          m_unk20;        // +0x20
    uint64_t          m_unk28;        // +0x28
    void*             m_pTypeTable0;  // +0x30  (= &xmmword_1835B5AA8)
    uint64_t          m_unk38;        // +0x38
    void*             m_pTypeTable1;  // +0x40  (= &xmmword_1835B5AA8)
    uint64_t          m_unk48;        // +0x48
    int32_t           m_typeIndex;    // +0x50  (xmmword_1835B5AA8 element index)
    uint32_t          _pad54;         // +0x54
    uint64_t          m_unk58;        // +0x58
};
static_assert(sizeof(S_VariableReference) == 0x60, "S_VariableReference embedded value (ctor sub_180207B44)");

}  // namespace wh::xgenaimodule
