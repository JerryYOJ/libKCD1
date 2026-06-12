#pragma once

// -----------------------------------------------
// I_MinigameElementsController — minigame UI interface
// -----------------------------------------------
// Warhorse: wh::guimodule::I_MinigameElementsController
// RTTI: .?AVI_MinigameElementsController@guimodule@wh@@
//
// PRIMARY (+0x00) base of wh::guimodule::C_UIMinigameElements. wh:: type ->
// vtable NOT interfuscated. Modeled in Offsets:: namespace for layout reuse.
//
// NOTE: NO virtual destructor — exactly ONE slot (same pattern as
// I_EventLogListener: 1-slot interface, dtor lives on the implementer's
// IUIGameEventSystem vtable, [0] thunk sub_180B1AF58 -> sub_181146CC8).
//
// Binary vtable @ 0x1826d29e0 (1 slot, implementer C_UIMinigameElements):
//   [0] 0x00  sub_1806F8740 = { *(int*)(this+0x40) = value; } — plain setter
//             of C_UIMinigameElements::m_value40 (semantic name UNVERIFIED)

namespace Offsets {

struct I_MinigameElementsController {
    virtual void _vf0(int value) = 0;    // [0] 0x00  sub_1806F8740 (writes this+0x40)
};

}  // namespace Offsets
