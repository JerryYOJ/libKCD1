#pragma once

// -----------------------------------------------
// IGameObjectView — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryAction/IGameObject.h
// C_Actor implementation vtable: 0x1821B6DA8 (at object +0x40)
// C_Player implementation vtable: 0x1826C3E10 (at object +0x40)
//
// 3 slots. Slot [0] is a destructor thunk that adjusts this by -0x40.

namespace Offsets {

struct IGameObjectView {
    virtual void Dtor(char flags) = 0;                                 // [0] 0x00
    virtual void UpdateView(void* pViewParams) = 0;                    // [1] 0x08  SViewParams&
    virtual void PostUpdateView(void* pViewParams) = 0;                // [2] 0x10  SViewParams&
};

} // namespace Offsets
