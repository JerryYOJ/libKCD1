#pragma once
#include <cstdint>

// -----------------------------------------------
// IActionListener — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryAction/IGameFramework.h
// RTTI: .?AUIActionListener@@
// Binary vtable for C_UIMap at 0x1826d1680 (3 slots):
//   [0] sub_180B1AF34  Dtor thunk (this -= 0x10)

namespace Offsets {

struct IActionListener {
    virtual void Dtor(char flags) = 0;                                         // [0] 0x00
    virtual void OnAction(void* actionId, int activationMode, float value) = 0; // [1] 0x08  0x1801FF728
    virtual void AfterAction() = 0;                                            // [2] 0x10  0x1802004AC
};

}  // namespace Offsets
