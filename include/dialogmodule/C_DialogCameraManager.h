#pragma once
#include <cstdint>
#include "Offsets/vtables/I_DialogCameraManager.h"
#include "Offsets/vtables/IEntitySystemSink.h"

// -----------------------------------------------
// C_DialogCameraManager — owns the dialogue cameras and proxies the active one
// -----------------------------------------------
// RTTI: .?AVC_DialogCameraManager@dialogmodule@wh@@  (wh::dialogmodule)
// Constructor:  sub_180FD1F94  — constructs the 4 C_AnimatedCamera variants and
//               registers the manager as an IEntitySystemSink.
// Allocated by: sub_180FDBD1C (the dialog-module init that registers the
//               wh_dlg_* CVars incl. wh_dlg_NoCameras); cached at dialog-
//               instance +0x118. Size = 0xB8.
//
// Inheritance (RTTI class-hierarchy, MI — two polymorphic bases):
//   [+0x00] I_DialogCameraManager  — camera-control interface (7 slots; the
//                                     vtable @0x1826b3820 carrying FillViewParams)
//   [+0x08] IEntitySystemSink      — entity-system event sink (7 slots)
//
// The manager caches the active camera's transform in its own +0x48/+0x58/+0x64
// fields; FillViewParams (slot 2) copies those into the S_ViewParams out struct
// and FORCES the 2.35 aspect + constrain flag — the source of the dialogue
// "base" letterbox bars. The four C_AnimatedCamera variants are the framing
// shots (master / close-up / medium / wide).

namespace wh::dialogmodule {

class C_AnimatedCamera;   // per-shot camera (0xD0); held by pointer only

class C_DialogCameraManager
    : public Offsets::I_DialogCameraManager   // +0x00 (7 slots; FillViewParams etc.)
    , public Offsets::IEntitySystemSink       // +0x08 (7 slots)
{
public:
    inline static constexpr auto VTABLE = Offsets::VTABLE_C_DialogCameraManager;

    void*             _unk10;            // +0x10
    C_AnimatedCamera* m_camera0;         // +0x18  framing-shot cameras (master/closeup/
    C_AnimatedCamera* m_camera1;         // +0x20  medium/wide; exact mapping TBD)
    C_AnimatedCamera* m_camera2;         // +0x28
    void*             _unk30;            // +0x30
    C_AnimatedCamera* m_camera3;         // +0x38
    C_AnimatedCamera* m_activeCamera;    // +0x40  currently-selected camera (0 = none)
    Quat              m_rotation;        // +0x48  cached active-camera orientation (w=1 init)
    Vec3              m_position;        // +0x58  cached active-camera position
    float             m_fov;            // +0x64  cached vertical FOV (60.0f init)
    uint8_t           _unk68[0x0C];      // +0x68
    int32_t           _unk74;            // +0x74  (= 2 init)
    void*             _unk78;            // +0x78
    int32_t           _unk80;            // +0x80  (= 5 init)
    uint8_t           m_activated;       // +0x84  Activate sets 1, Deactivate sets 0
    uint8_t           m_active;          // +0x85  IsActive gate (= 1 init)
    uint8_t           _pad86[2];         // +0x86
    void*             _unk88;            // +0x88  (_vf6 predicate target)
    void*             _unk90;            // +0x90  (_vf5 predicate target)
    void*             _unk98;            // +0x98
    int32_t           _unkA0;            // +0xA0
    uint8_t           _unkA4[4];         // +0xA4
    uint8_t           _unkA8;            // +0xA8
    uint8_t           _unkA9;            // +0xA9  (= 1 init)
    uint8_t           m_justActivated;   // +0xAA  one-shot, transferred to S_ViewParams+0xB0
    uint8_t           _unkAB[5];         // +0xAB
    int64_t           _unkB0;            // +0xB0  (init ~ -100000 timestamp/marker)
};

static_assert(sizeof(C_DialogCameraManager) == 0xB8);
static_assert(offsetof(C_DialogCameraManager, m_activeCamera) == 0x40);
static_assert(offsetof(C_DialogCameraManager, m_rotation)     == 0x48);
static_assert(offsetof(C_DialogCameraManager, m_position)     == 0x58);
static_assert(offsetof(C_DialogCameraManager, m_fov)          == 0x64);
static_assert(offsetof(C_DialogCameraManager, m_activated)    == 0x84);
static_assert(offsetof(C_DialogCameraManager, m_justActivated) == 0xAA);

}  // namespace wh::dialogmodule
