#pragma once

#include <cstdint>

// -----------------------------------------------
// IGameObjectProfileManager — Binary vtable order (interfuscated)
// -----------------------------------------------
// SDK: CryEngine/CryAction/IGameObject.h
// C_Actor implementation vtable: 0x1821B6DC8 (at object +0x48)
// C_Player implementation vtable: 0x1826C3DA0 (at object +0x48)
//
// 3 slots. Slot [0] is a destructor thunk that adjusts this by -0x48.
// Slot [1] in C_Actor: sub_1805DD224 — checks *(this+0x130)
// Slot [2] in C_Actor: ret false

namespace Offsets {

struct IGameObjectProfileManager {
    virtual void Dtor(char flags) = 0;                                 // [0] 0x00
    virtual bool SetAspectProfile(uint32_t aspect, uint8_t profile) = 0; // [1] 0x08
    virtual uint8_t GetDefaultProfile(uint32_t aspect) = 0;           // [2] 0x10
};

} // namespace Offsets
