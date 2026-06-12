#pragma once
#include <cstdint>

// -----------------------------------------------
// IFlashPlayer_RenderProxy — Binary vtable order (INTERFUSCATED)
// -----------------------------------------------
// SDK: CryEngine CryCommon/IFlashPlayer.h (<interfuscator:shuffle> block lines 211-215).
// RTTI: .?AUIFlashPlayer_RenderProxy@@ (global namespace, struct)
// Impl: second base of CFlashPlayer at +0x08 -> vtable 0x1821bc4d8 (4 slots)
//       (RTTI COL this_off == 8; slots adjust `this` by -8 to reach CFlashPlayer).
//
// The render thread invokes these callbacks after CFlashPlayer::Render /
// the lockless playback path enqueued them on the renderer (vf+0x350 of
// *(player+0xC8)+0x38). Each callback pushes the player's stereo/compositing
// state (player +0x18/+0x1C/+0x20/+0x21) into the GFx renderer object
// (+0x344/+0x350..+0x352/+0x48..+0x4A) before drawing.

namespace Offsets {

struct IFlashPlayer_RenderProxy {
    enum EFrameType { EFT_Mono, EFT_StereoLeft, EFT_StereoRight };

    // Binary vtable 0x1821bc4d8 (4 slots)
    virtual void RenderCallback(EFrameType ft, bool releaseOnExit = true) = 0;
        // [0] 0x00 sub_1803E8AA0 — locks player CS (+0xF8); renderer+0x351 = ft!=0,
        //     +0x352 = ft==1; copies player stereo/canvas flags; compositing depth
        //     (+0x18) > 0 -> renderer vf+0xE8; draws movie (+0xB0/vf+0x130);
        //     releaseOnExit -> vcall player Release
    virtual void RenderPlaybackLocklessCallback(int cbIdx, EFrameType ft, bool finalPlayback = true,
                                                bool releaseOnExit = true) = 0;
        // [1] 0x08 sub_180E73CF8 — command buffer element *(player+0x120) + 0x38*cbIdx;
        //     same renderer flag push; playback sub_180E799F4, finalPlayback ->
        //     sub_180E73FB4 (buffer reset); releaseOnExit -> Release
    virtual void DummyRenderCallback(EFrameType ft, bool releaseOnExit = true) = 0;
        // [2] 0x10 sub_180E6E798 — no-op except optional player Release
    virtual ~IFlashPlayer_RenderProxy() {}
        // [3] 0x18 sub_180B19D84 — thunk: scalar deleting dtor on player (this-8, sub_1805573E4)
};

}  // namespace Offsets
