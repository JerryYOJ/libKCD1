#pragma once

#include <cstdint>
#include <cstddef>

#include "C_POI.h"        // reuse global ::_reference_target_int (defined there); single-TU umbrella build -> must NOT redefine
#include "I_Location.h"   // 2nd base (interface)

// ===========================================================================
// wh::rpgmodule::C_RPGLocation  -  runtime crime/RPG location object.
// ===========================================================================
// RTTI: .?AVC_RPGLocation@rpgmodule@wh@@   (TD 0x182a66f80 / img 0x2A66F80)
// Bases (per RTTI base array):
//   [+0x00]  ::_reference_target<int>   CryEngine refcount for _smart_ptr; int refcount @+0x08;
//            primary vtable 0x182307170 / COL 0x182307168.
//            Modeled by REUSING ::_reference_target_int (from C_POI.h) -- layout-identical (0x10).
//            NOTE: the binary primary vtable has only 1 real slot (sub_1811BB274) before the
//            I_Location COL; the reused replica declares 4 inline virtuals. This is irrelevant
//            to layout (one vptr regardless) -- do NOT claim primary-vtable fidelity for this base.
//   [+0x10]  I_Location                 interface; vtable 0x182307180 / COL 0x182307178.
//
// Allocated by C_RPGLocationManager via operator new(0x38) (sub_180208CA8 / sub_18119AD64).
// The pointer handed to callers is the I_Location* subobject (= this + 0x10).
//
// Member offsets are relative to the C_RPGLocation base; the I_Location virtuals see them
// as (I_Location* + 0x..) = (C_RPGLocation + 0x..) - 0x10.
// Abstract (I_Location pure virtuals not overridden here) -> never instantiated in this TU.
// ===========================================================================

namespace wh::rpgmodule {

struct S_Location;   // +0x18: static location definition (opaque; resolved by CryGUID, not RE'd)

class C_RPGLocation
    : public ::_reference_target_int   // +0x00  refcount base (vtable + int refcount @+0x08)
    , public I_Location                // +0x10  location interface (vtable only)
{
public:
    const S_Location* m_pLocationDef;     // +0x18  static location definition; factory sub_180208CA8 sets it = sub_1811968C0(&guid)
                                          //        (lookup in std::unordered_map<CryGUID, const S_Location*> registry dword_1835A8458).
                                          //        GetWUID (sub_1804989B8) reads it and calls def->vtbl[0] to yield the WUID. [CONFIRMED ptr; S_Location not RE'd]
    Vec3              m_position;         // +0x20  position override; (0,0,0) => compute from node AABB [CONFIRMED sub_1811C3238]
    uint32_t          m_unk2C;            // +0x2C  zero-initialised; meaning unknown [UNVERIFIED]
    E_CrimeIconLevel  m_selfWantedLevel;  // +0x30  own wanted level [CONFIRMED sub_1806F8600 / sub_18027CFC4]
    uint32_t          _pad34;             // +0x34  alignment to 0x38
};
static_assert(sizeof(C_RPGLocation) == 0x38, "ctor operator new(0x38) in sub_180208CA8");

}  // namespace wh::rpgmodule
