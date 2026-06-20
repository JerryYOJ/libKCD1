#pragma once
#include <cstdint>

// -----------------------------------------------
// I_DialogCameraManager — dialog-camera control interface
// -----------------------------------------------
// Warhorse: wh::dialogmodule::I_DialogCameraManager (RTTI-confirmed: the
// primary (+0x00) base of C_DialogCameraManager; the other base is
// IEntitySystemSink at +0x08). Modeled in Offsets:: for layout reuse, like
// Offsets::I_HUDElementsController. wh:: type -> NOT interfuscated, so slot
// order == declaration order.
//
// Binary vtable (the C_DialogCameraManager override) @ 0x1826b3820, 7 slots.
// Several impls are shared with C_AnimatedCamera (e.g. IsActive sub_1803E6C14),
// consistent with both deriving from this interface.

namespace wh::dialogmodule { struct S_ViewParams; }

namespace Offsets {

struct I_DialogCameraManager {
    virtual bool IsActive() = 0;                                            // [0] 0x00  sub_1803E6C14 (this+0x85 && (_vf5() || this+0x40))
    virtual void _vf1() = 0;                                                // [1] 0x08  empty (CFG-guard nop)
    virtual void FillViewParams(wh::dialogmodule::S_ViewParams* out) = 0;   // [2] 0x10  sub_1806FCC50 — copies pos/quat/fov, FORCES aspect=2.35 + constrain
    virtual void Activate() = 0;                                            // [3] 0x18  sub_180FD2950 — sets this+0x84=1, applies active camera + DoF
    virtual void Deactivate() = 0;                                          // [4] 0x20  sub_180FD319C — sets this+0x84=0, resets DoF
    virtual bool _vf5() = 0;                                                // [5] 0x28  sub_180FD3AA8 — returns this+0x90 != 0
    virtual bool _vf6() = 0;                                                // [6] 0x30  sub_180FD39B4 — returns this+0x88 != 0
};

}  // namespace Offsets
