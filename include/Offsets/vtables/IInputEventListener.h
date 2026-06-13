#pragma once

#include "SInputEvent.h"

// -----------------------------------------------
// IInputEventListener — raw input callback (register via IInput::AddEventListener)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IInput.h. RTTI: .?AUIInputEventListener@@
// Binary vtable (e.g. C_UIActionHintManager +0x08 subobject @ 0x1826ccfb8),
// declaration order (NOT shuffled):
//   [0] sub_180B1AE38  deleting-dtor adjustor thunk (this -= 8)
//   [1] sub_1803E6900  OnInputEvent — VERIFIED: reads SInputEvent.keyId(+0x10),
//       keyName(+0x08), deviceId(+0x00); returns true to CONSUME the event.
//   [2] sub_180434C90  OnInputEventUI — default `return false`
//   [3] sub_1803953E0  GetPriority    — default `return 0`

namespace Offsets {

struct IInputEventListener {
    virtual void Dtor(char flags) = 0;                                  // [0] +0x00
    virtual bool OnInputEvent(const SInputEvent& event) = 0;            // [1] +0x08  true = consume
    virtual bool OnInputEventUI(const void* unicodeEvent) = 0;          // [2] +0x10  const SUnicodeEvent& (rarely used)
    virtual int  GetPriority() const = 0;                              // [3] +0x18  higher = earlier
};

}  // namespace Offsets
