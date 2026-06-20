#pragma once

#include <cstdint>
#include <vector>
#include "C_IntelligentObject.h"   // the AI-object spine (C_AIObject..C_IntelligentObject, 0x178) -- primary base
#include "I_Area.h"                // the identity sub-object @+0x218 (AsArea())
// CryStringT<char> / Vec3 come from the PCH prelude.

// ===========================================================================
// wh::xgenaimodule::C_SmartArea  (size 0x440)  RTTI .?AVC_SmartArea@xgenaimodule@wh@@
// ===========================================================================
// A world region primitive (WUID type 7). Owns its geometry (AABB + boundary polygon) and a set of
// tags; the location system resolves a point to a C_SmartArea and maps its WUID to a C_RPGLocation.
// Created by the SmartArea manager (factory sub_1815EA2D0: operator new(0x440) + ctor sub_1815CC0F0);
// resolve by key via C_SmartAreaManager::ResolveWuid; get the area(s) at a point via the manager's
// EnumerateAreasAtPoint (global C_RegularGrid). Parent area = raw field m_parent (+0x238).
//
// MODELING NOTE: C_SmartArea is a deep multiple-inheritance object with a VIRTUAL base, and its
// secondary interface sub-objects are INTERLEAVED with data fields, so C++ inheritance cannot reproduce
// the exact layout. We therefore model the primary spine via inheritance (C_IntelligentObject) and lay
// the rest out as a flat, byte-exact field map: interleaved secondary-base vtable pointers and un-RE'd
// embedded objects are kept as opaque regions (clearly named). The full base/vtable map is documented
// in the SmartArea recon. Real bases per RTTI: C_SmartEntity(+0x00), I_RWLocked(+0x60),
// I_SmartEntitySubbrainListener(+0x178), I_SmartEntity(+0x180), I_Area(+0x218),
// I_TemplateIdentification(+0x438, virtual). Layout VERIFIED (factory new 0x440 + ctor sub_1815CC0F0).
// ===========================================================================

namespace wh::xgenaimodule {

class C_SmartArea : public C_IntelligentObject {   // +0x000  C_AIObject..C_IntelligentObject spine (m_key WUID @+0x08)
public:
    // --- C_SmartEntity additions (0x178..0x218): subbrain-listener/smart-entity sub-object vtables,
    //     the virtual-base vbptr (+0x188) + vtordisp (+0x184), and the subbrain/behavior container
    //     (+0x190). Kept opaque (virtual-inheritance plumbing; not needed to use a SmartArea). ---
    uint8_t            m_smartEntityRegion[0xA0];   // +0x178  (I_SmartEntitySubbrainListener@+0x178,
                                                    //          I_SmartEntity@+0x180, vbptr@+0x188, subbrain@+0x190)

    // --- C_SmartArea identity + geometry (0x218..) ---
    void*              m_areaVtbl;          // +0x218  I_Area sub-object vtable (use AsArea())
    std::vector<void*> m_childAreas;        // +0x220  {begin,end,cap}; 8-byte elems [purpose UNVERIFIED: child/linked areas]
    C_SmartArea*       m_parent;            // +0x238  parent area (null at top); resolver walks this
    uint64_t           m_unk240;            // +0x240  [UNVERIFIED]
    std::vector<Vec3>  m_boundaryPoints;    // +0x248  boundary polygon {begin,end,cap} (I_Area::GetBoundaryPoints)
    float              m_height;            // +0x260  init -1.0f (I_Area slot7) [likely Z-extent]
    Vec3               m_aabbMin;           // +0x264  AABB min (ctor inits +1e15; I_Area::GetAABB/ContainsPoint)
    Vec3               m_aabbMax;           // +0x270  AABB max (ctor inits -1e15)
    uint8_t            m_unk27C[0xC];       // +0x27C  not ctor-inited [UNVERIFIED: center/origin or pad]

    uint8_t            m_varRef[0x60];      // +0x288  embedded S_VariableReference (ctor sub_180207B44) [opaque]
    uint8_t            m_embed2E8[0x40];    // +0x2E8  embedded object (ctor sub_1807402B4) [type UNVERIFIED]
    uint8_t            m_embed328[0x40];    // +0x328  embedded container (ctor sub_180F39820) [type UNVERIFIED]
    CryStringT<char>   m_label;             // +0x368  area label (brain var "Label"; ctor + sub_1815D1888)
    uint8_t            m_embed370[0x40];    // +0x370  embedded object w/ inner array (ctor sub_1815CAC14) [type UNVERIFIED]
    uint8_t            m_unk3B0[0x10];      // +0x3B0  vector/smart-ptr {+0x3B0,+0x3B8} [UNVERIFIED]
    uint64_t           m_unk3C0;            // +0x3C0  [UNVERIFIED]
    uint64_t           m_unk3C8;            // +0x3C8  [UNVERIFIED]
    std::vector<CryStringT<char>> m_tags1;  // +0x3D0  sorted tag set #1 (I_Area::HasTag binary-search)
    std::vector<CryStringT<char>> m_tags2;  // +0x3E8  sorted tag set #2 (I_Area::HasTag; built by sub_1815D1888)

    uint8_t            m_ownership[0x38];   // +0x400  embedded wh::xgenaimodule::C_Ownership (vtable @+0x400) [opaque]
    void*              m_templateIdVtbl;    // +0x438  I_TemplateIdentification virtual-base vtable (returns 3)

    // --- typed accessors over the embedded sub-objects (no construction; views over `this`) ---
    I_Area*       AsArea()       { return reinterpret_cast<I_Area*>(reinterpret_cast<char*>(this) + 0x218); }
    C_SmartArea*  GetParent() const { return m_parent; }   // raw field; NOT a virtual (resolver reads +0x238)
};
static_assert(sizeof(C_SmartArea) == 0x440, "C_SmartArea (factory operator new 0x440; ctor sub_1815CC0F0)");

}  // namespace wh::xgenaimodule
