#pragma once

// -----------------------------------------------
// I_DialogUIController — dialog-UI operations interface
// -----------------------------------------------
// Warhorse: wh::dialogmodule::I_DialogUIController  (note: DIALOGMODULE, not
// guimodule — the dialog system calls into the UI through this interface).
// RTTI: .?AVI_DialogUIController@dialogmodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UIInteractiveDialog. wh:: type ->
// vtable NOT interfuscated, slot order == declaration order. Modeled in the
// Offsets:: namespace for layout reuse (same convention as
// I_HUDElementsController).
//
// Binary vtable @ 0x1826d17e8 (11 slots, sole implementer C_UIInteractiveDialog).
// Method semantics were NOT deep-dived; names kept as _vfN with per-slot
// evidence notes. The element drives the "IDialog" Flash event system (topics,
// haggling input, skill checks) — see C_UIInteractiveDialog.h.
//
//   [0]  0x00  ??_G (deleting dtor; ICF-shared COMDAT symbol
//              "__ExceptionPtr::scalar deleting destructor")
//   [1]  0x08  sub_18112A2FC  (0xB4 bytes)
//   [2]  0x10  sub_18113637C  (0x268)
//   [3]  0x18  sub_1811365E4  (0x1EB; refs "default", "dialog_haggling")
//   [4]  0x20  sub_181138958  (0x91)
//   [5]  0x28  sub_1811395E4  thunk: this+0x18 (= &m_eventSender) ->
//              sub_181122C9C (send through the SUIEventSenderDispatcher)
//   [6]  0x30  sub_1811389EC  (0xA3)
//   [7]  0x38  sub_18112A54C  (0x6B)
//   [8]  0x40  sub_18112A4A0  (0xAA; refs "default")
//   [9]  0x48  sub_18113956C  (0x77)
//   [10] 0x50  sub_1806FE7D0  = { m_flag98 = 0; } (clears byte at this+0x98)

namespace Offsets {

struct I_DialogUIController {
    virtual void Dtor(char flags) = 0;   // [0]  0x00
    virtual void _vf1() = 0;             // [1]  0x08  sub_18112A2FC
    virtual void _vf2() = 0;             // [2]  0x10  sub_18113637C
    virtual void _vf3() = 0;             // [3]  0x18  sub_1811365E4 ("dialog_haggling")
    virtual void _vf4() = 0;             // [4]  0x20  sub_181138958
    virtual void _vf5() = 0;             // [5]  0x28  sub_1811395E4 -> sub_181122C9C(&m_eventSender)
    virtual void _vf6() = 0;             // [6]  0x30  sub_1811389EC
    virtual void _vf7() = 0;             // [7]  0x38  sub_18112A54C
    virtual void _vf8() = 0;             // [8]  0x40  sub_18112A4A0
    virtual void _vf9() = 0;             // [9]  0x48  sub_18113956C
    virtual void _vf10() = 0;            // [10] 0x50  sub_1806FE7D0 (clears flag +0x98)
};

}  // namespace Offsets
