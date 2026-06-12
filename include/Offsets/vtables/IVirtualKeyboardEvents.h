#pragma once
#include <cstdint>

// -----------------------------------------------
// IVirtualKeyboardEvents — Binary vtable order
// -----------------------------------------------
// SDK: CryEngine CryCommon/IPlatformOS.h (virtual-keyboard completion callbacks)
// RTTI: .?AUIVirtualKeyboardEvents@@  (GLOBAL namespace SDK struct)
//
// Binary vtable for wh::guimodule::CUIInput (+0x08 subobject) @ 0x1822e8ae8
// (3 slots):
//   [0] sub_180B1AED4  deleting-dtor adjustor thunk (this -= 8)
//   [1] sub_181131A74  KeyboardCancelled — sends "Input" sender event id 1
//                      ("OnKeyboardCancelled") via CUIInput::m_eventSenderMap
//                      (send helper sub_181133538(this-8, 1, args))
//   [2] sub_181131AA8  KeyboardFinished  — wraps the input text in a
//                      CryStringT<char> argument and sends event id 0
//                      ("OnKeyboardDone") via sub_181133538(this-8, 0, args)
//
// Slot->name mapping verified behaviorally against the events the two
// implementations send (Cancelled -> OnKeyboardCancelled, Finished ->
// OnKeyboardDone). Parameter is consumed as a char string (CryStringT<char>
// ctor wh::framework::StringHash_18028CEA4).

namespace Offsets {

struct IVirtualKeyboardEvents {
    virtual void Dtor(char flags) = 0;                       // [0] 0x00
    virtual void KeyboardCancelled() = 0;                    // [1] 0x08
    virtual void KeyboardFinished(const char* pInString) = 0; // [2] 0x10
};

}  // namespace Offsets
