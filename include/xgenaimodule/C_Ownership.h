#pragma once

#include <cstdint>
#include <vector>
#include "../framework/WUID.h"   // wh::framework::WUID (owner/owned handles)

// ===========================================================================
// wh::xgenaimodule::C_Ownership  -  an owner/owned WUID pair + a list of owned WUIDs.
// ===========================================================================
// RTTI: .?AVC_Ownership@xgenaimodule@wh@@ (TD 0x182b1cc38); base I_Ownership. vtable 0x1821BD628
// (16 slots). size 0x30. Embedded value member (e.g. C_SmartArea+0x400, C_AIInventory+0x130).
// m_owner/m_owned default to the invalid-WUID sentinel qword_183016A58 (== 0xFFFFFFFFFFFFFFFF;
// getter sub_1807060E0). m_ownedList is freed as 8-byte trivial elements -> std::vector<WUID>.
// Slots [0..8] VERIFIED by decompile (GetOwnerOrSelf sub_18024D158, GetOwnedCount = (end-begin)>>3);
// [9..15] not individually decompiled (slot count is firm). The I_Ownership base contributes the
// single vtable; modeled here directly on C_Ownership.
// ===========================================================================

namespace wh::xgenaimodule {

class C_Ownership {
public:
    virtual ~C_Ownership();                   // [0]  scalar-deleting dtor (sub_1815C02C0 -> sub_18055F234)
    virtual bool  _vf1();                      // [1]  returns 1
    virtual wh::framework::WUID* GetOwnerOrSelf();       // [2]  sub_18024D158 (&m_owned, or &m_owner if owned is sentinel)
    virtual wh::framework::WUID* GetOwnerRef();          // [3]  returns &m_owner
    virtual wh::framework::WUID* GetOwnedRef();          // [4]  returns &m_owned
    virtual void  SetOwner(const wh::framework::WUID* v); // [5]  m_owner = *v
    virtual void  SetOwned(const wh::framework::WUID* v); // [6]  m_owned = *v
    virtual bool  _vf7();                       // [7]  returns 1
    virtual int   GetOwnedCount();             // [8]  m_ownedList size ((end-begin)>>3)
    virtual void  _vf9();                       // [9]
    virtual void  _vf10();                      // [10]
    virtual void  _vf11();                      // [11]
    virtual void  _vf12();                      // [12]
    virtual void  _vf13();                      // [13]
    virtual void  _vf14();                      // [14]
    virtual void  _vf15();                      // [15]

    wh::framework::WUID              m_owner;     // +0x08  owner handle (init = invalid-WUID sentinel)
    wh::framework::WUID              m_owned;     // +0x10  owned handle (init = invalid-WUID sentinel)
    std::vector<wh::framework::WUID> m_ownedList; // +0x18  owned WUIDs (GetOwnedCount)
};
static_assert(sizeof(C_Ownership) == 0x30, "C_Ownership embedded value (verified via C_AIInventory embed + dtor)");

}  // namespace wh::xgenaimodule
