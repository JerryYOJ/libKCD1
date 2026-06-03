#pragma once

#include <cstdint>
#include "T_ObjectManagerBase.h"
#include "../framework/WUID.h"

// ===========================================================================
// wh::xgenaimodule::C_LinkablesManager — the registry of C_LinkableObjects (chests/stashes/shops/
// world items), keyed by WUID. Global *qword_1837999D8; ctor sub_181676778; size 0x1A8.
// Primary vtable 0x18270E720 (RTTI .?AVC_LinkablesManager@xgenaimodule@wh@@, COL 0x1825A9BF0).
//
// It is the concrete instantiation of T_ObjectManagerBase (size 0x58). The full base chain —
// verified from the RTTI base-class array (PMD member offsets) — is a single-inheritance chain that
// splits into the two callback holders at the bottom (offsets are within the object):
//
//   C_LinkablesManager
//    : T_ObjectManagerBase<C_LinkableObject, C_LinkablesManager>                       @+0x00  map (0x58)
//      : Callbacks::C_NoDataExtension<Functor2<E_AIONotifyEvent::Type,const WUID&>,1>  @+0x00
//        : Callbacks::C_Extension<void, Functor2<...>, 1, 1>                           @+0x00
//          : Callbacks::C_NoDataExtensionBase<Functor2<...>, 1>                        @+0x00  vtable owner
//            : Callbacks::C_CallbackListHolder<C_Callback<void,Functor2<...>,void>>    @+0x08  callback set ptr
//            , Callbacks::C_TrackSequencing<1>                                         @+0x10  re-entrancy guard
//
// The 0x148 secondary index + init flag are C_LinkablesManager's OWN members (NOT in the template):
// proven by the sibling C_IntelligentObjectManager, which reuses the SAME 0x58 template but has no
// secondary index (size 0x68). Net layout: vtable@+0x00, callback-set@+0x08, guard@+0x10,
// WUID->object map@+0x18, secondary index@+0x58, init flag@+0x1A0. Use Find to resolve a chest WUID.
// ===========================================================================

namespace wh::xgenaimodule {

class C_LinkableObject;

// Secondary index attached to a linkables-style manager (0x148 bytes; ctor sub_1815FDC4C,
// dtor sub_1815FE220). Aggregates two small sub-structs (+0x00, +0x40 via sub_1807402B4), one
// @+0x80 (sub_180719114), a SECOND pooled WUID hash map @+0xC0 (a reverse / by-type index, same
// shape as T_WuidHashMap), one @+0x100 (sub_180F994DC) and a dword @+0x140. Sub-object internals
// are not individually RE'd — modeled opaque to the VERIFIED size so the parent layout stays exact.
struct S_AIObjectSecondaryIndex { uint8_t _opaque[0x148]; };

class C_LinkablesManager
    : public T_ObjectManagerBase<C_LinkableObject, C_LinkablesManager>   // @+0x00 (0x58)
{
public:
    static C_LinkablesManager* GetInstance();                      // *qword_1837999D8 (null before the AI module is up)
    C_LinkableObject*          Find(wh::framework::WUID w) const;  // engine map-find (sub_18024D6E4) -> object or null

    S_AIObjectSecondaryIndex   m_secondaryIndex;  // +0x58  reverse / by-type index (0x148)
    uint8_t                    m_initialized;     // +0x1A0 ctor sets 1 last
    uint8_t                    _pad1A1[7];
};
static_assert(sizeof(C_LinkablesManager) == 0x1A8);

}  // namespace wh::xgenaimodule
