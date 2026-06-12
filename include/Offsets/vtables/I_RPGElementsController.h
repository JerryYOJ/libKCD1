#pragma once

// -----------------------------------------------
// I_RPGElementsController — buff/levelup/perk HUD interface
// -----------------------------------------------
// Warhorse: wh::guimodule::I_RPGElementsController
// RTTI: .?AVI_RPGElementsController@guimodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UIRPGElements. wh:: type -> vtable
// NOT interfuscated, slot order == declaration order. Modeled in Offsets::
// namespace for layout reuse.
//
// NOTE: NO virtual destructor — slot [0] is a regular method (same pattern as
// I_EventLogListener). The deleting dtor of the implementer lives on its
// IUIGameEventSystem vtable ([0] thunk sub_180B1AF70 -> sub_181146D8C).
//
// Binary vtable @ 0x1826d2880 (4 slots, implementer C_UIRPGElements):
//   [0] 0x00  sub_181152FD4  (this, const CryStringT&, const CryStringT&, bool)
//             -> sub_18113EB1C(&m_eventSender, str1, str2, ..., flag): sends a
//             two-string "RPGElements" event (buff add/change family)
//   [1] 0x08  sub_181154C80  (0x7A; refs "OnLearnPerkResult" — sends the
//             learn-perk result to the Inventory Flash element)
//   [2] 0x10  sub_1811534A0  (0x68)
//   [3] 0x18  sub_181151550  (0x51)

namespace Offsets {

struct I_RPGElementsController {
    virtual void _vf0(const CryStringT<char>& a, const CryStringT<char>& b, bool flag) = 0; // [0] 0x00  sub_181152FD4 (sends 2-string buff event; exact event UNVERIFIED)
    virtual void _vf1() = 0;             // [1] 0x08  sub_181154C80 ("OnLearnPerkResult")
    virtual void _vf2() = 0;             // [2] 0x10  sub_1811534A0
    virtual void _vf3() = 0;             // [3] 0x18  sub_181151550
};

}  // namespace Offsets
