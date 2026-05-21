#pragma once
#include <cstdint>

// -----------------------------------------------
// I_RandomEventListener — random encounter callbacks during FT
// -----------------------------------------------
// RTTI: .?AVI_RandomEventListener@playermodule@wh@@
// Binary vtable for C_FastTravel at 0x1826dd700 (12 slots)

namespace wh::playermodule {

struct I_RandomEventListener {
    virtual void _vf0() {}    // [0]
    virtual void _vf1() {}    // [1]
    virtual void _vf2() {}    // [2]
    virtual void _vf3() {}    // [3]
    virtual void _vf4() {}    // [4]
    virtual void _vf5() {}    // [5]
    virtual void _vf6() {}    // [6]
    virtual void _vf7() {}    // [7]
    virtual void _vf8() {}    // [8]
    virtual void _vf9() {}    // [9]
    virtual void _vf10() {}   // [10]
    virtual void _vf11() {}   // [11]
};

}  // namespace wh::playermodule
