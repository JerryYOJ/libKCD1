#pragma once
#include <cstdint>
#include <cstddef>

// -----------------------------------------------------------------------------
// SCameraParams — TrackView / cut-scene camera parameters (KCD/Warhorse layout).
// -----------------------------------------------------------------------------
// Our own RE definition. The stock CryCommon IMovieSystem.h SCameraParams is a
// trimmed/wrong variant AND that header drags in the whole CryEngine SDK
// (ISystem/ICryPak/IComponent -> boost), so it cannot be included here.
//
// Verified against WHGame.dll:
//   - built by   CAnimSceneNode::ApplyCameraKey   (sub_181E347B8)
//   - copied 0x24 bytes by CMovieSystem::SetCameraParams (sub_181E3E948)
//   - consumed by CViewSystem::SetActiveCamera    (sub_181ABA1E8)
//   - bCustomAspect/fAspectRatio drive the in-engine cut-scene letterbox; the
//     TrackView producer sub_181E030B4 sets them from the camera entity flags
//     (bit 0x1000000 -> 2.35f, bit 0x100 -> 16:9).
//   - +0x14/+0x18 are blend speeds (named by the SelectKey XML serializer
//     sub_181E3E23C), NOT camera dimensions.

struct SCameraParams {
    uint32_t cameraEntityId;  // +0x00  EntityId
    float    fFOV;            // +0x04  vertical FOV (radians)
    float    fNearZ;          // +0x08  near plane
    float    fFarZ;           // +0x0C  far plane (0 == use default) [INFERRED: position,
                              //        set 0.0 in cutscenes, not read-verified]
    bool     justActivated;   // +0x10  camera just activated this frame
    bool     bBlendOut;       // +0x11  blend back to pre-sequence view on end
    // +0x12..+0x13 padding
    float    fBlendPosSpeed;  // +0x14  camera-cut position blend speed
    float    fBlendRotSpeed;  // +0x18  camera-cut rotation blend speed
    bool     bCustomAspect;   // +0x1C  custom-aspect (letterbox) enable flag
    // +0x1D..+0x1F padding
    float    fAspectRatio;    // +0x20  cinematic aspect (e.g. 2.35f) -> letterbox
};

static_assert(sizeof(SCameraParams) == 0x24, "SCameraParams must be 0x24 (SetCameraParams copies 0x24 bytes)");
static_assert(offsetof(SCameraParams, fFarZ)         == 0x0C, "");
static_assert(offsetof(SCameraParams, justActivated) == 0x10, "");
static_assert(offsetof(SCameraParams, fBlendPosSpeed) == 0x14, "");
static_assert(offsetof(SCameraParams, bCustomAspect) == 0x1C, "");
static_assert(offsetof(SCameraParams, fAspectRatio)  == 0x20, "");
