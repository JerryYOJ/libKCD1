#pragma once
#include <cstdint>

// -----------------------------------------------
// I_ReadinessDebuggable — Warhorse debug interface
// -----------------------------------------------
// RTTI: .?AVI_ReadinessDebuggable@wh@@
// Binary vtable for C_FastTravel at 0x1826dd728 (7 slots)

namespace wh {

class I_ReadinessDebuggable {
public:
    virtual void _vf0() = 0;   // [0] 0x00
    virtual void _vf1() = 0;   // [1] 0x08
    virtual void _vf2() = 0;   // [2] 0x10
    virtual void _vf3() = 0;   // [3] 0x18
    virtual void _vf4() = 0;   // [4] 0x20
    virtual void _vf5() = 0;   // [5] 0x28
    virtual void _vf6() = 0;   // [6] 0x30
};

}  // namespace wh
