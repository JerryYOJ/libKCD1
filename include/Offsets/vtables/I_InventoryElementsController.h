#pragma once

// -----------------------------------------------
// I_InventoryElementsController — inventory popup-dialog API
// -----------------------------------------------
// Warhorse: wh::guimodule::I_InventoryElementsController
// RTTI: .?AVI_InventoryElementsController@guimodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UIInventoryElements. wh:: type —
// NOT interfuscated, slot order == declaration order. Modeled in Offsets::
// exactly like Offsets::I_HUDElementsController.
//
// Binary vtable for C_UIInventoryElements @ 0x1826d1780 (2 slots; the qword
// at 0x1826d1790 is the RTTI COL of the next vtable):
//   [0] sub_181129BFC  deleting dtor (frees sender event-map node 0x28 +
//                      receiver dispatcher map, rewinds vtables to
//                      I_InventoryElementsController/IUIPseudoRTTI)
//   [1] sub_1811399A8  ShowInfoDialog(const CryStringT<char>& message) —
//                      copies the string (sub_18028D178 = CryStringT copy)
//                      and fires the "InventoryElements" system->UI event 0
//                      "ShowInfoDialog" via the sender dispatcher at +0x10
//                      (sub_181122F88).

namespace Offsets {

struct I_InventoryElementsController {
    virtual void Dtor(char flags) = 0;                              // [0] 0x00  sub_181129BFC
    virtual void ShowInfoDialog(const CryStringT<char>& msg) = 0;   // [1] 0x08  sub_1811399A8
};

}  // namespace Offsets
