#pragma once
#include <cstdint>

// -----------------------------------------------
// I_RandomEventListener — random encounter callbacks during FT
// -----------------------------------------------
// RTTI: .?AVI_RandomEventListener@playermodule@wh@@
// C_FastTravel's primary vtable 0x1826dd700 has exactly 4 slots (the next
// COL sits at +0x20; the old "12 slots" count ran past it into the adjacent
// I_ReadinessDebuggable vtable at 0x1826dd728): 3 interface slots here plus
// the deriver's appended virtual dtor (C_FastTravel slot [3] = sub_18121DE9C).
// Slot names below describe the C_FastTravel overrides; the interface-level
// names are unverified, hence _vfN.

namespace wh::playermodule {

class I_RandomEventListener {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_RandomEventListener;
    virtual void _vf0() {}    // [0]  C_FastTravel: sub_1806BEEB0 release-pair no-op
    virtual void _vf1() {}    // [1]  C_FastTravel: sub_181223D98 refresh pending event prompt
    virtual void _vf2() {}    // [2]  C_FastTravel: sub_1806F7CC4 = if (IsFastTravelling()) Stop()
};

}  // namespace wh::playermodule
