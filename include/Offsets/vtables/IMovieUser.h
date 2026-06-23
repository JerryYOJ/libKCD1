#pragma once

// -----------------------------------------------
// IMovieUser — CryEngine movie-system "user" callback interface.
// -----------------------------------------------
// CViewSystem implements it (it is CViewSystem's base @ +0x08). The SDK tags this
// interface <interfuscator:shuffle>, so the SDK declaration order is NOT reliable;
// the slot order below is the VERIFIED binary order of CViewSystem's IMovieUser
// vtable @ RVA 0x2766C70 (each slot resolved by address). This is the vtable the
// cut-scene letterbox hook patches (slot 1 = SetActiveCamera).

struct SCameraParams;  // crysystem/SCameraParams.h

namespace Offsets {

struct IMovieUser {
    virtual ~IMovieUser() {}                                                // [0] (scalar deleting dtor) 0x180B1C588
    virtual void SetActiveCamera(const SCameraParams& params) = 0;          // [1] sub_181ABA1E8
    virtual void BeginCutScene(void* pSeq, unsigned long flags, bool bResetFX) = 0;  // [2] sub_181A99304
    virtual void EndCutScene(void* pSeq, unsigned long flags) = 0;          // [3] sub_181A9E318
    virtual void SendGlobalEvent(const char* pszEvent) = 0;                 // [4]
    virtual void PlaySubtitles(void* pSeq, void* pSound) = 0;               // [5]
};

}  // namespace Offsets
