#pragma once
#include <cstdint>

// -----------------------------------------------
// IUIGameEventSystem — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine CryAction/IFlashUI.h (extends IUIPseudoRTTI)
// RTTI: .?AUIUIGameEventSystem@@
//
// Binary vtable (8 slots, from C_UIMap @ 0x1826d16f0):
//   [0] Dtor                                    sub_181129CF0
//   [1] GetName() → const char*                 sub_1806FE810 ("UIMap")
//   [2] InitEventSystem()                       sub_18112FC58 (registers Flash events)
//   [3] nop
//   [4] nop
//   [5] Update()                                called per-frame from CUIManager::OnPostUpdate
//   [6] nop
//   [7] nop

namespace Offsets {

struct IUIGameEventSystem {
    virtual void Dtor(char flags) = 0;                      // [0] 0x00
    virtual const char* GetName() = 0;                      // [1] 0x08
    virtual void InitEventSystem() = 0;                     // [2] 0x10
    virtual void _vf3() = 0;                                // [3] 0x18
    virtual void _vf4() = 0;                                // [4] 0x20
    virtual void Update() = 0;                              // [5] 0x28
    virtual void _vf6() = 0;                                // [6] 0x30
    virtual void _vf7() = 0;                                // [7] 0x38
};

}  // namespace Offsets
