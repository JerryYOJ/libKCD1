#pragma once
#include <cstdint>

// -----------------------------------------------
// I_ShadowPlayHightlightCountListener — Binary vtable order (wh:: type, NOT shuffled)
// -----------------------------------------------
// Warhorse: wh::game::I_ShadowPlayHightlightCountListener
// (sic — "Hightlight" typo is Warhorse's own, from the RTTI string)
// RTTI: .?AVI_ShadowPlayHightlightCountListener@game@wh@@
// Modeled in Offsets:: for layout reuse (same approach as I_LocationListener).
//
// Binary vtable for wh::guimodule::C_UIMenuEvents (+0x08 subobject)
// @ 0x1822ed240 (1 slot — NO virtual dtor):
//   [0] sub_181155770  highlight-count callback; feeds the
//                      "NVidiaShadowPlayStatus" (Active, Records) flash event
//                      registered by C_UIMenuEvents (sender event id 8)
//
// Registration: C_UIMenuEvents::Init (IUIModule slot [1], sub_18114B0C4)
// pushes this+8 into the vector at *(S_GameContext+0x88)+0x30.

namespace Offsets {

struct I_ShadowPlayHightlightCountListener {
    virtual void OnHighlightCount() = 0;  // [0] 0x00  sub_181155770 (name UNVERIFIED; semantics from usage)
};

}  // namespace Offsets
