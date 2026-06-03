#pragma once

#include <cstdint>
#include "T_ObjectManagerBase.h"   // wh::xgenaimodule::T_ObjectManagerBase<>, T_WuidHashMap<>, Callbacks chain
#include "C_IntelligentObject.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::C_IntelligentObjectManager
//   The global WUID -> C_IntelligentObject* registry. Singleton: *qword_183799950
//   (GetInstance = sub_180705DE0, indirected via data slot off_1829D1BF0).
//   ctor sub_1815A60A8 ; lazy alloc+ctor sub_1815A85D4 (malloc 0x68, accounted via
//   _InterlockedExchangeAdd(&dword_183002E60, 0x68) @0x1815A8695). size 0x68 (VERIFIED).
//
//   Primary vtable     0x182702BA0 (RTTI .?AVC_IntelligentObjectManager@xgenaimodule@wh@@,
//                      TD 0x182B17940, COL 0x18258F198, offsetToTop=0, CHD 0x18258EF80, 8 bases).
//   I_DebugDraw vtable 0x182702B88 (secondary "_0", COL 0x18258F1C0, offsetToTop=0x60).
//   During-ctor vtable 0x182702B60 (the T_ObjectManagerBase base subobject, COL 0x18258F0F8).
//   vbtable            0x182702BC0 = {-0x58, +0x08}.
//
//   Inheritance VERIFIED from the RTTI base-class array (8 entries):
//     C_IntelligentObjectManager
//       : public          T_ObjectManagerBase<C_IntelligentObject, C_IntelligentObjectManager> @+0x00 (0x58)
//           : Callbacks::C_NoDataExtension< Functor2<E_AIONotifyEvent::Type,const WUID&>, 1 >   @+0x00
//             : C_Extension : C_NoDataExtensionBase (vtable owner)                              @+0x00
//                 : C_CallbackListHolder @+0x08 , C_TrackSequencing<1> @+0x10
//       , public virtual  I_DebugDraw                                                           @+0x60
//         (vbptr @+0x58 -> vbtable 0x182702BC0; RTTI base PMD mdisp=0, pdisp=0x58, vdisp=4)
//
//   Net layout: vptr@+0x00, callbackSet@+0x08, guard@+0x10, WUID->object map@+0x18 (0x40),
//   vbptr@+0x58, I_DebugDraw vbase@+0x60. This is the MINIMAL manager variant: no secondary index
//   (contrast C_LinkablesManager, which adds a 0x148 index @+0x58 -> size 0x1A8). The map is exactly
//   T_WuidHashMap<C_IntelligentObject*>.
//
//   Populated by the C_IntelligentObject ctor (sub_180278388 @0x1802784A0:
//   sub_1802782D0(qword_183799950, this, &this->m_wuid@+0x08)). Key = C_IntelligentObject::m_wuid;
//   value = the object* (node+0x18). Resolved by C_InformationManager's holder-collection path
//   (sub_1802B5470) and ~9 other call sites of Find (sub_1802B620C).
//
//   Sibling singletons in the same AI-object registry family (all key the SAME object's WUID up its
//   single-inheritance chain): qword_1837999E0 (C_AIObject), qword_1837999D8 (C_LinkablesManager),
//   qword_1837999D0 (C_MessageCapableObject mgr), qword_183799950 (this).
// ===========================================================================

namespace wh::xgenaimodule {

// ---------------------------------------------------------------------------
// I_DebugDraw — minimal debug-visualization interface; a VIRTUAL base of the AI
// managers. Interface vtable 0x1821A4878 (RTTI .?AVI_DebugDraw@xgenaimodule@wh@@,
// TD 0x182B16590, COL 0x182452928). Exactly two slots; the draw hook is empty in
// retail (folded onto the CFG no-op 0x1802E39B0). The draw method's exact
// name/signature is UNVERIFIED (cannot be recovered from an empty body).
// ---------------------------------------------------------------------------
class I_DebugDraw {
public:
    virtual ~I_DebugDraw();                 // [0] 0x18159B0A8
    virtual void DebugDraw();               // [1] empty default (0x1802E39B0) [name UNVERIFIED]
};

class C_IntelligentObjectManager
    : public T_ObjectManagerBase<C_IntelligentObject, C_IntelligentObjectManager>   // @+0x00 (0x58)
    , public virtual I_DebugDraw                                                     // vbase @+0x60 (vbptr @+0x58)
{
public:
    static C_IntelligentObjectManager* GetInstance();   // -> *qword_183799950 (sub_180705DE0)

    // --- engine ops (non-virtual; address forwarders, see Offsets.cpp) ---
    C_IntelligentObject* Find(wh::framework::WUID w) const;   // sub_1802B620C: FNV-1a-64 the WUID, bucket-walk, value@node+0x18; null on miss
    bool                 Register(C_IntelligentObject* obj);  // sub_1802782D0: insert (key = obj->m_wuid) if absent, Notify(Added); true if inserted

    // --- T_ObjectManagerBase virtual overrides (primary vtable 0x182702BA0) ---
    void Unregister(const wh::framework::WUID& key) override;  // [2] sub_180278644: erase-by-WUID + Notify(Removed)
    void Clear() override;                                     // [3] sub_1815A7308: Notify(Removed) all + reset pool (COMDAT-shared w/ C_LinkablesManager)

    // --- I_DebugDraw override (secondary vtable 0x182702B88) ---
    void DebugDraw() override;                                 // empty (no-op) in retail (0x1802E39B0)
};
static_assert(sizeof(C_IntelligentObjectManager) == 0x68);

}  // namespace wh::xgenaimodule
