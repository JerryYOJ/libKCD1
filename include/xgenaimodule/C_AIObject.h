#pragma once

#include <cstdint>
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::C_AIObject — root of the AI-object hierarchy.
// ===========================================================================
// RTTI: Warhorse no-RTTI base (custom castable/capability interface).
// Ctor:    sub_1804505F4(this, &wuid, host)
// vtable:  0x1821AD630 (9 slots) — verified by diff vs derived classes.
// Registers `this` into the C_AIObject WUID registry qword_1837999E0
// (std::unordered_map<WUID, C_AIObject*>; the map the Information single-holder
// query path resolves through, then filters by GetCapabilityFlags()&0x40).
//
// Subclasses: C_LinkableObject -> C_MessageCapableObject -> C_IntelligentObject
//             -> { C_NPC, C_SmartEntity }.
//
// size 0x60.
// ===========================================================================

namespace wh::xgenaimodule {

class C_AIPuppet;   // the embodied AI agent (world transform + movement); see m_pHost

class C_AIObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AIObject;
    // --- primary vtable, 9 slots (slot bodies are the C_AIObject base versions;
    //     C_LinkableObject/C_MessageCapableObject/C_IntelligentObject override 0,1,2) ---
    virtual void     OnInit();                 // [0] +0x00  per-level init/registration hook  [name inferred]
    virtual          ~C_AIObject();            // [1] +0x08  (scalar-deleting dtor in binary)
    virtual uint32_t GetCapabilityFlags();     // [2] +0x10  bitmask: &0x40=info-holder, &0x1=link, sign-bit=...
    virtual void*    GetTransform();           // [3] +0x18  reads m_pHost(+0x58); position/transform  [name UNVERIFIED]
    virtual void     HostNotify();             // [4] +0x20  -> m_pHost->vtbl[+0x70]()  [name UNVERIFIED]
    virtual void*    HostQuery();              // [5] +0x28  -> m_pHost->vtbl[+0x88]()  [name UNVERIFIED]
    virtual void*    GetTypeDescriptor0();     // [6] +0x30  -> &qword_18372ED28 (per-class static)  [name UNVERIFIED]
    virtual void*    GetTypeDescriptor1();     // [7] +0x38  -> qword_183785B60  (per-class static)  [name UNVERIFIED]
    virtual void     vf08_Hook();              // [8] +0x40  empty hook (no-op)

    // --- fields (verified from ctor sub_1804505F4) ---
    wh::framework::WUID m_wuid;                 // +0x08  registry key; high byte = E_WUIDType tag
    uint8_t             m_pool[0x24];           // +0x10  small fixed pool (sub_1804217C8(.,0xC,3,sub_1802E7190)) [UNVERIFIED]
    int32_t             m_idx34;                // +0x34  init -1
    int32_t             m_idx38;                // +0x38  init -1
    char                _pad3C[4];              // +0x3C
    void*               m_unk40;               // +0x40  init 0 [UNVERIFIED]
    void*               m_unk48;               // +0x48  init 0 [UNVERIFIED]
    uint16_t            m_unk50;               // +0x50  init 0 [UNVERIFIED]
    char                _pad52[6];              // +0x52
    C_AIPuppet*         m_pHost;               // +0x58  host/owner (ctor arg a3). VERIFIED concrete type for C_NPC:
                                               //        wh::xgenaimodule::C_AIPuppet (vtable 0x1821C7D10, RTTI .?AVC_AIPuppet@xgenaimodule@wh@@) —
                                               //        the embodied agent (world transform @+0x08, movement sub-obj @+0x38).
                                               //        Declared static type may be a base interface (slot-3 handles non-puppet hosts).
};
static_assert(sizeof(C_AIObject) == 0x60);

}  // namespace wh::xgenaimodule
