#pragma once

#include <cstdint>

#include "../framework/WUID.h"   // wh::framework::WUID (GetOrCreateLocationByKey)

// ===========================================================================
// wh::rpgmodule::I_RPGLocationManager  -  C_RPGLocationManager primary interface.
// ===========================================================================
// RTTI: .?AVI_RPGLocationManager@rpgmodule@wh@@   (TD 0x182a62030 / img 0x2A62030)
// Primary base of C_RPGLocationManager (+0x00). PURE interface (sizeof 0x08).
// Primary vtable: 0x1826d3c30. Slot 0 is the (scalar-deleting) destructor.
// Only the verified slots are named; the rest are placeholders. NOT interfuscated
// (wh:: type -> canonical order). Vtable extends beyond slot [39].
// ===========================================================================

namespace wh::rpgmodule {

class I_Location;          // returned by GetOrCreateLocationByKey
struct S_LocationArea;     // opaque query region for EnumerateLocationsInArea [UNVERIFIED]

class I_RPGLocationManager {
public:
    virtual ~I_RPGLocationManager() = 0;   // [0]  0x00  dtor (sub_1811A2DEC)
    virtual void _vf1()  = 0;   // [1]  0x08  sub_1811938DC [UNVERIFIED]
    virtual void _vf2()  = 0;   // [2]  0x10  sub_1803DBDF0 [UNVERIFIED]
    // [3]  0x18  collect every I_Location overlapping a region into an out-list [CONFIRMED sub_1802088F4]
    virtual void EnumerateLocationsInArea(const S_LocationArea* area, void* outList) = 0;
    virtual void _vf4()  = 0;   // [4]  0x20  sub_181197DE4 [UNVERIFIED]
    virtual void _vf5()  = 0;   // [5]  0x28  sub_181197D58 [UNVERIFIED]
    virtual void _vf6()  = 0;   // [6]  0x30  sub_181197C10 [UNVERIFIED]
    virtual void _vf7()  = 0;   // [7]  0x38  sub_181197C5C [UNVERIFIED]
    // [8]  0x40  get-or-create the C_RPGLocation for a WUID key, return its I_Location* [CONFIRMED sub_180208C40 -> sub_180208CA8]
    virtual I_Location* GetOrCreateLocationByKey(const wh::framework::WUID& key) = 0;
    virtual void _vf9()  = 0;   // [9]  0x48  sub_181193884 [UNVERIFIED]
    virtual void _vf10() = 0;   // [10] 0x50  sub_181193844 [UNVERIFIED]
    virtual void _vf11() = 0;   // [11] 0x58  sub_1811A2C48 [UNVERIFIED]
    virtual void _vf12() = 0;   // [12] 0x60  sub_1811989AC [UNVERIFIED]
    virtual void _vf13() = 0;   // [13] 0x68  sub_181199BAC [UNVERIFIED]
    virtual void _vf14() = 0;   // [14] 0x70  sub_1811995D8 [UNVERIFIED]
    virtual void _vf15() = 0;   // [15] 0x78  sub_1806FF200 [UNVERIFIED]
    virtual void _vf16() = 0;   // [16] 0x80  sub_181198AD4 [UNVERIFIED]
    virtual void _vf17() = 0;   // [17] 0x88  sub_18069FB90 [UNVERIFIED]
    virtual void _vf18() = 0;   // [18] 0x90  sub_181198A5C [UNVERIFIED]
    virtual void _vf19() = 0;   // [19] 0x98  sub_1806F3298 [UNVERIFIED]
    virtual void _vf20() = 0;   // [20] 0xA0  sub_1811994C4 [UNVERIFIED]
    virtual void _vf21() = 0;   // [21] 0xA8  sub_181198C9C [UNVERIFIED]
    virtual void _vf22() = 0;   // [22] 0xB0  sub_181198CD0 [UNVERIFIED]
    virtual void _vf23() = 0;   // [23] 0xB8  sub_1811977BC [UNVERIFIED]
    virtual void _vf24() = 0;   // [24] 0xC0  sub_1811979D4 [UNVERIFIED]
    virtual void _vf25() = 0;   // [25] 0xC8  sub_181197748 [UNVERIFIED]
    virtual void _vf26() = 0;   // [26] 0xD0  sub_1811907E0 [UNVERIFIED]
    virtual void _vf27() = 0;   // [27] 0xD8  sub_18119E128 [UNVERIFIED]
    virtual void _vf28() = 0;   // [28] 0xE0  sub_181197CC8 [UNVERIFIED]
    virtual void _vf29() = 0;   // [29] 0xE8  sub_181193CE8 [UNVERIFIED]
    virtual void _vf30() = 0;   // [30] 0xF0  sub_181193F58 [UNVERIFIED]
    virtual void _vf31() = 0;   // [31] 0xF8  sub_1811A43CC [UNVERIFIED]
    virtual void _vf32() = 0;   // [32] 0x100 sub_1811A60D0 [UNVERIFIED]
    virtual void _vf33() = 0;   // [33] 0x108 sub_181192FA8 [UNVERIFIED]
    virtual void _vf34() = 0;   // [34] 0x110 sub_1811938F0 [UNVERIFIED]
    virtual void _vf35() = 0;   // [35] 0x118 sub_181197660 [UNVERIFIED]
    virtual void _vf36() = 0;   // [36] 0x120 sub_1811976AC [UNVERIFIED]
    virtual void _vf37() = 0;   // [37] 0x128 sub_1806CB684 [UNVERIFIED]
    // [38] 0x130  remove a listener from the change-notify vector (+0x270) [CONFIRMED sub_1806BD5F8]
    virtual void RemoveListener(void* listener) = 0;
    virtual void _vf39() = 0;   // [39] 0x138 sub_18119C448 (vtable continues past here) [UNVERIFIED]
};
static_assert(sizeof(I_RPGLocationManager) == 0x08, "pure interface: vtable pointer only");

}  // namespace wh::rpgmodule
