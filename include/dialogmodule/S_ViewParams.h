#pragma once
#include <cstdint>

// -----------------------------------------------
// S_ViewParams — Warhorse camera -> view params (filled by a dialog camera)
// -----------------------------------------------
// The output struct that I_DialogCameraManager::FillViewParams (sub_1806FCC50)
// fills each frame for the active dialog camera. This is NOT the CryEngine
// ::SViewParams (IViewSystem.h) — the field offsets differ (fov is at +0x30
// here vs +0x20 in the SDK struct, and there is an explicit aspect + letterbox
// pair the SDK struct lacks). It is a custom Warhorse view-setup struct.
//
// Only the fields written by FillViewParams are verified (offsets confirmed
// from the decompile); the gaps are consumed elsewhere by the view system and
// are left as padding. The total size is therefore a lower bound, not certain,
// so this struct is meant for pointer reinterpretation (we never allocate it).
//
// The dialogue "base bars" come from FillViewParams forcing:
//   m_constrainAspect = 1   and   m_aspect = 2.35f
// which makes the renderer letterbox the (narrower) view into the screen.

namespace wh::dialogmodule {

struct S_ViewParams {
    Vec3     m_position;          // +0x00  view position        (from camera/manager pos)
    Quat     m_rotation;          // +0x0C  view orientation      (from camera/manager quat)
    uint8_t  _pad1C[0x14];        // +0x1C  (view-system fields; unverified)
    float    m_fov;               // +0x30  vertical FOV          (from manager+0x64)
    uint8_t  m_constrainAspect;   // +0x34  letterbox / aspect-constrain enable (forced 1)
    uint8_t  _pad35[3];           // +0x35
    float    m_aspect;            // +0x38  forced view aspect    (forced 2.35f)
    uint8_t  _pad3C[0x74];        // +0x3C  (view-system fields; unverified)
    uint8_t  m_justActivated;     // +0xB0  one-shot "camera just activated" flag
};

static_assert(offsetof(S_ViewParams, m_position)       == 0x00);
static_assert(offsetof(S_ViewParams, m_rotation)       == 0x0C);
static_assert(offsetof(S_ViewParams, m_fov)            == 0x30);
static_assert(offsetof(S_ViewParams, m_constrainAspect) == 0x34);
static_assert(offsetof(S_ViewParams, m_aspect)         == 0x38);
static_assert(offsetof(S_ViewParams, m_justActivated)  == 0xB0);

}  // namespace wh::dialogmodule
