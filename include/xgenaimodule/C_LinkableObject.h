#pragma once

#include <cstdint>
#include "C_AIObject.h"

// ===========================================================================
// wh::xgenaimodule::C_LinkableObject : C_AIObject, I_RWLocked
// ===========================================================================
// Ctor:    sub_180450530(this, &wuid, host)
// vtable:  0x1821AD5A8 (16 slots) — overrides slots 0/1/2, adds 9..15.
// Introduces a SECOND polymorphic base at +0x60: wh::xgenaimodule::I_RWLocked
// (a read/write-lock mixin; identity from C_NPC RTTI / classinformer). Its
// 3 vtable slots are no-op stubs at the C_IntelligentObject level.
// Registers into qword_1837999D8.
// size 0xA0.
// ===========================================================================

namespace wh::xgenaimodule {

// 3-slot read/write-lock mixin; second base of C_LinkableObject at +0x60.
// Name from C_NPC RTTI base list. Exact lock semantics UNVERIFIED.
class I_RWLocked {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_RWLocked;
    virtual ~I_RWLocked();   // [0]
    virtual void vf1();      // [1]  (lock/unlock primitive — UNVERIFIED)
    virtual void vf2();      // [2]
};

class C_LinkableObject : public C_AIObject, public I_RWLocked {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LinkableObject;
    // --- primary-vtable additions (slots 9..15) ---
    virtual void* GetTypeDescriptor2();   // [9]  +0x48  -> off_1829DAFC0 (static)  [name UNVERIFIED]
    virtual void* GetTypeDescriptor3();   // [10] +0x50  -> off_1829DAFC8 (static)  [name UNVERIFIED]
    virtual void* GetTypeInfo();          // [11] +0x58  -> off_1829DAFD0 (static type-info provider)  [name UNVERIFIED]
    virtual bool  vf12();                 // [12] +0x60  -> false (default predicate)
    virtual bool  vf13();                 // [13] +0x68  -> false
    virtual bool  vf14();                 // [14] +0x70  -> true
    virtual bool  vf15();                 // [15] +0x78  -> true

    // --- fields (ctor zeroes +0x68..+0x98) ---
    void* m_unk68;   // +0x68  [UNVERIFIED]
    void* m_unk70;   // +0x70  [UNVERIFIED]
    void* m_unk78;   // +0x78  [UNVERIFIED]
    void* m_unk80;   // +0x80  [UNVERIFIED]
    void* m_unk88;   // +0x88  [UNVERIFIED]
    void* m_unk90;   // +0x90  [UNVERIFIED]
    void* m_unk98;   // +0x98  [UNVERIFIED]
};
static_assert(sizeof(C_LinkableObject) == 0xA0);

}  // namespace wh::xgenaimodule
