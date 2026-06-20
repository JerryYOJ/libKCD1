#pragma once

#include "C_LinkableObject.h"

// ===========================================================================
// wh::xgenaimodule::C_DynamicLinkableObject : C_LinkableObject
// ===========================================================================
// A runtime-registered ("dynamic") linkable AI object (WUID type 10 = DynamicLinkableObject;
// see E_WUIDType). RTTI: .?AVC_DynamicLinkableObject@xgenaimodule@wh@@ (TD img 0x2B207B8).
//
// ctor sub_180450300: builds the C_LinkableObject base (sub_180450530 -> C_AIObject sub_1804505F4),
// OVERRIDES the primary vtable (+0x00) and the I_RWLocked secondary vtable (+0x60) with the DLO's,
// then registers `this` into the dynamic-linkable registry qword_1837999C0. It writes NO fields
// beyond the C_LinkableObject base, so the object is layout-identical to C_LinkableObject (0xA0) --
// only the two vtables differ. (Used as the base of per-node BT runner contexts, e.g.
// S_RemoveItemContext.)
// ===========================================================================

namespace wh::xgenaimodule {

class C_DynamicLinkableObject : public C_LinkableObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DynamicLinkableObject;
    // Overrides the C_AIObject/C_LinkableObject primary slots and the I_RWLocked secondary vtable
    // (installed by ctor sub_180450300). May add slots beyond C_LinkableObject's 16 [UNVERIFIED],
    // but adds no data members -- size stays 0xA0.
    ~C_DynamicLinkableObject() override;   // [0]
};
static_assert(sizeof(C_DynamicLinkableObject) == 0xA0);

}  // namespace wh::xgenaimodule
