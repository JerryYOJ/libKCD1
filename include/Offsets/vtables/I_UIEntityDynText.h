#pragma once

// -----------------------------------------------
// I_UIEntityDynText — dynamic per-entity Flash text tags
// -----------------------------------------------
// Warhorse: wh::guimodule::I_UIEntityDynText
// RTTI: .?AVI_UIEntityDynText@guimodule@wh@@
//
// Base (+0x08) of wh::guimodule::C_UIInteractiveDialog. wh:: type -> vtable
// NOT interfuscated, slot order == declaration order. Modeled in Offsets::
// namespace for layout reuse.
//
// Drives the "EntityFlashTag" dyn-texture material
// ("Materials\gfx\EntityFlashTag") — the in-world Flash text rendered above
// entities (dialog/bark bubbles), closely related to CUIEntityDynTexTag.
//
// Binary vtable @ 0x1826d1848 (4 slots, implementer C_UIInteractiveDialog):
//   [0] 0x00  sub_180B1AEF8  adjustor thunk (this-8) -> deleting dtor
//   [1] 0x08  sub_18112A2A4  (0x56; refs "Materials\gfx\EntityFlashTag",
//             "EntityFlashTag")
//   [2] 0x10  sub_1811376F8  (0x2B)
//   [3] 0x18  sub_181138B60  (0x176; refs "EntityFlashTag")

namespace Offsets {

struct I_UIEntityDynText {
    virtual void Dtor(char flags) = 0;   // [0] 0x00
    virtual void _vf1() = 0;             // [1] 0x08  sub_18112A2A4 (EntityFlashTag material)
    virtual void _vf2() = 0;             // [2] 0x10  sub_1811376F8
    virtual void _vf3() = 0;             // [3] 0x18  sub_181138B60 (EntityFlashTag)
};

}  // namespace Offsets
