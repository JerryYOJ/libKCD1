#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <boost/container/vector.hpp>     // count-based {ptr,size,cap} sorted tag sets
#include "C_SmartEntity.h"               // primary parent (spine + virtual base I_TemplateIdentification)
#include "I_Area.h"                      // identity sub-object @+0x218
#include "S_VariableReference.h"         // embedded value @+0x288
#include "C_Ownership.h"                 // embedded value @+0x400
#include "../framework/CryStringHash.h"  // std::hash<CryStringT<char>> for the name-keyed maps
// CryStringT<char> / Vec3 come from the PCH prelude.

// ===========================================================================
// wh::xgenaimodule::C_SmartArea : C_SmartEntity, I_Area   (size 0x440)
// ===========================================================================
// RTTI: .?AVC_SmartArea@xgenaimodule@wh@@. A world region primitive (WUID type 7): owns its geometry
// (XY boundary polygon + AABB) and two sorted tag sets, exposes a "parentArea" Lua variable, forms a
// parent/child area tree, and is tracked by C_SmartAreaManager (qword_183785A20). Created by the
// manager factory (operator new(0x440) + ctor sub_1815CC0F0); the I_TemplateIdentification virtual
// base (from C_SmartEntity) lands at +0x438 with MSVC's vtordisp at +0x434; I_Area is a vtable-only
// identity sub-object at +0x218 and C_SmartArea's own fields follow at +0x220.
//
// Layout VERIFIED byte-exact from ctor sub_1815CC0F0, member-dtor sub_1815CD644 (per-member
// destructor calls reveal element types), I_Area accessors (ContainsPoint sub_180375AB8 / GetAABB
// sub_1815D3A18 / GetBoundaryPoints sub_180655C14 / GetHeight sub_1806F99C0 / HasTag sub_180428068),
// and SetParent sub_1815DD4A0. The two name-keyed maps and the set carry trivial 8-byte values whose
// exact element type is UNVERIFIED (no insert/lookup site was localized -- only ctor/clear/dtor); the
// KEYS are confirmed CryStringT<char> (node dtors call StringHashCleanup on the key).
// ===========================================================================

namespace wh::xgenaimodule {

// Force the vtordisp before the I_TemplateIdentification virtual base so the layout matches retail
// (vtordisp @+0x434, vbase @+0x438). MSVC's default (/vd1) omits it here, landing the vbase at +0x430.
#pragma vtordisp(push, 2)
class C_SmartArea : public C_SmartEntity, public I_Area {   // C_SmartEntity @+0x00, I_Area @+0x218
public:
    // override the virtual-base virtual (SmartArea's template-type id == 3); makes MSVC place the vtordisp.
    int GetTemplateType() override;   // [I_TemplateIdentification] sub_180B1C650 -> 3

    // --- own fields (+0x220 .. +0x430) ---
    std::vector<C_SmartArea*>                m_childAreas;        // +0x220  child areas (non-owning; built by SetParent)
    C_SmartArea*                             m_parent;            // +0x238  parent area (null at top of the tree)
    void*                                    m_parentLinkHandle;  // +0x240  cached handle from the parent's variable store
                                                                  //         (SetParent: parent+0x58->GetStore->vtbl+0x10; 0 when detached)
    std::vector<Vec3>                        m_boundaryPoints;    // +0x248  XY boundary polygon (I_Area::GetBoundaryPoints)
    float                                    m_height;            // +0x260  area height, init -1.0f (I_Area::GetHeight)
    Vec3                                     m_aabbMin;           // +0x264  AABB min, init +1e15 (inverted) (ContainsPoint/GetAABB)
    Vec3                                     m_aabbMax;           // +0x270  AABB max, init -1e15
    float                                    _unk27C;             // +0x27C  not ctor-inited [UNVERIFIED]
    bool                                     m_parentLinkValid;   // +0x280  set when the parentArea var/link is established
    uint8_t                                  _pad281[7];          // +0x281  -> +0x288
    S_VariableReference                      m_parentAreaVar;     // +0x288  the lazily-created "parentArea" Lua variable (sub_1815CEBF8)
    std::unordered_map<CryStringT<char>, void*> m_mapA;           // +0x2E8  key=CryStringT (StringHash); value=trivial 8-byte [UNVERIFIED]
    std::unordered_map<CryStringT<char>, void*> m_mapB;           // +0x328  key=CryStringT (StringHash); value=trivial 8-byte [UNVERIFIED]
    CryStringT<char>                         m_label;             // +0x368  "Label" brain-variable text
    std::unordered_set<void*>                m_members;           // +0x370  objects tracking this area via their +0x1E0 back-ref
                                                                  //         (reparented to m_parent on removal; element type UNVERIFIED)
    std::vector<Vec3>                        m_boundaryPoints2;   // +0x3B0  second Vec3 polygon (cleared during "inside" var setup; purpose UNVERIFIED)
    void*                                    m_pResolvedSystem;   // +0x3C8  subsystem resolved from the parent (sub_1815C8EB4) [UNVERIFIED type]
    boost::container::vector<CryStringT<char>> m_tags1;           // +0x3D0  sorted tag set, registered with the manager (I_Area::HasTag)
    boost::container::vector<CryStringT<char>> m_tags2;           // +0x3E8  sorted tag set, rebuilt by sub_1815D1888 (I_Area::HasTag fallback)
    C_Ownership                              m_ownership;         // +0x400  owner/owned WUIDs (0x30)
    // MSVC appends here: vtordisp @+0x434, then virtual base I_TemplateIdentification @+0x438; object ends 0x440.

    // identity sub-object access (proper upcast, not a raw pointer)
    I_Area*      AsArea()          { return static_cast<I_Area*>(this); }
    C_SmartArea* GetParent() const { return m_parent; }   // raw field +0x238 (not a virtual)
};
#pragma vtordisp(pop)
static_assert(sizeof(C_SmartArea) == 0x440, "C_SmartArea (factory operator new 0x440; ctor sub_1815CC0F0)");

}  // namespace wh::xgenaimodule
