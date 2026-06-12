#pragma once
#include <cstdint>

// -----------------------------------------------
// IHardwareMouseEventListener — Binary vtable order
// -----------------------------------------------
// SDK: CryEngine CryCommon/IHardwareMouse.h
// RTTI: .?AUIHardwareMouseEventListener@@  (GLOBAL namespace SDK struct)
//
// Binary vtable for wh::guimodule::CUIInput (+0x10 subobject) @ 0x1822e8b08
// (2 slots):
//   [0] sub_180B1AEE0  deleting-dtor adjustor thunk (this -= 0x10)
//   [1] sub_18050015C  OnHardwareMouseEvent
//
// Listener is registered in CUIInput's ctor sub_181124858:
//   gEnv.pHardwareMouse(gEnv+0x110) vtbl+0x28 AddListener(this+0x10).
// SDK signature: OnHardwareMouseEvent(int iX, int iY,
//   EHARDWAREMOUSEEVENT eHardwareMouseEvent, int wheelDelta = 0).

namespace Offsets {

struct IHardwareMouseEventListener {
    virtual void Dtor(char flags) = 0;                                              // [0] 0x00
    virtual void OnHardwareMouseEvent(int iX, int iY, int eEvent, int wheelDelta) = 0; // [1] 0x08  sub_18050015C
};

}  // namespace Offsets
