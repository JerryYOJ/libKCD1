#pragma once

// -----------------------------------------------
// IInputEventListener — Binary vtable order
// -----------------------------------------------
// SDK: CryEngine CryCommon/IInput.h
// RTTI: .?AUIInputEventListener@@
//
// Binary vtable for C_UIActionHintManager (+0x08 subobject) @ 0x1826ccfb8
// (4 slots). Slot order matches the SDK declaration order exactly
// (~dtor, OnInputEvent, OnInputEventUI, GetPriority):
//   [0] sub_180B1AE38  deleting-dtor adjustor thunk (this -= 8)
//   [1] sub_1803E6900  OnInputEvent(const SInputEvent&) — reads deviceType
//       (+0x00), keyName (+0x08), keyId (+0x10); maps device to the mask
//       1=keyboard/mouse, 2=xboxpad, 4=ps4pad (keyName[0]=='p') and notifies
//       the owner — the same mask documented by the "InputDevice" param of
//       the ActionHints "OnInputDeviceChanged" event.
//   [2] sub_180434C90  OnInputEventUI — default `return false`
//   [3] sub_1803953E0  GetPriority    — default `return 0`

namespace Offsets {

struct IInputEventListener {
    virtual void Dtor(char flags) = 0;                       // [0] 0x00
    virtual bool OnInputEvent(const void* event) = 0;        // [1] 0x08  const SInputEvent&
    virtual bool OnInputEventUI(const void* event) = 0;      // [2] 0x10  default false
    virtual int  GetPriority() const = 0;                    // [3] 0x18  default 0
};

}  // namespace Offsets
