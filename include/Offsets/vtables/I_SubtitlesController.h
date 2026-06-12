#pragma once

// -----------------------------------------------
// I_SubtitlesController — subtitle display interface
// -----------------------------------------------
// Warhorse: wh::guimodule::I_SubtitlesController
// RTTI: .?AVI_SubtitlesController@guimodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UISubtitles. wh:: type -> vtable
// NOT interfuscated, slot order == declaration order. Modeled in Offsets::
// namespace for layout reuse.
//
// Binary vtable @ 0x1826d27f8 (3 slots, implementer C_UISubtitles):
//   [0] 0x00  sub_181146DF4  deleting dtor
//   [1] 0x08  sub_1811577E8  SetText(const CryStringT<char>& text, bool bForce)
//             — if wh_ui_SubtitlesEnabled->GetIVal() || bForce || text empty:
//             sends "Subtitles" event OnText(text) through m_eventSender
//             (sub_18113ED40); else sends the empty/clear form (sub_18113ECC4)
//   [2] 0x10  sub_181147570  Clear() { SetText("", false); } — re-dispatches
//             through vtbl[1] with an empty CryStringT

namespace Offsets {

struct I_SubtitlesController {
    virtual void Dtor(char flags) = 0;                                 // [0] 0x00
    virtual void SetText(const CryStringT<char>& text, bool bForce) = 0; // [1] 0x08  sub_1811577E8
    virtual void Clear() = 0;                                          // [2] 0x10  sub_181147570
};

}  // namespace Offsets
