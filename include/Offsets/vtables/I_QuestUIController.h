#pragma once

// -----------------------------------------------
// I_QuestUIController — quest-log UI interface
// -----------------------------------------------
// Warhorse: wh::questmodule::I_QuestUIController  (note: QUESTMODULE — the
// quest system pushes quest state into the UI through this interface).
// RTTI: .?AVI_QuestUIController@questmodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UIQuestLog. wh:: type -> vtable
// NOT interfuscated, slot order == declaration order. Modeled in Offsets::
// namespace for layout reuse.
//
// Binary vtable @ 0x1826d2950 (8 slots, implementer C_UIQuestLog). Method
// semantics not deep-dived (no string anchors in the bodies); the implementer
// emits the "QuestLog" events OnQuestInfo/OnQuestInfoEx/OnQuestDiary/
// OnQuestCanceled/OnQuestObjectTracked — see C_UIQuestLog.h.
//   [0] 0x00  sub_181146D0C  deleting dtor
//   [1] 0x08  sub_181156B70  (0x88)
//   [2] 0x10  sub_181156BF8  (0x135)
//   [3] 0x18  sub_181156A14  (0x159)
//   [4] 0x20  sub_181156D30  (0xCD)
//   [5] 0x28  sub_18115699C  (0x78)
//   [6] 0x30  sub_1811487B0  (0x65)
//   [7] 0x38  sub_181149290  (0x33)

namespace Offsets {

struct I_QuestUIController {
    virtual void Dtor(char flags) = 0;   // [0] 0x00
    virtual void _vf1() = 0;             // [1] 0x08  sub_181156B70
    virtual void _vf2() = 0;             // [2] 0x10  sub_181156BF8
    virtual void _vf3() = 0;             // [3] 0x18  sub_181156A14
    virtual void _vf4() = 0;             // [4] 0x20  sub_181156D30
    virtual void _vf5() = 0;             // [5] 0x28  sub_18115699C
    virtual void _vf6() = 0;             // [6] 0x30  sub_1811487B0
    virtual void _vf7() = 0;             // [7] 0x38  sub_181149290
};

}  // namespace Offsets
