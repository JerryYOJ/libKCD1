#pragma once
#include <cstdint>

// -----------------------------------------------
// IMovieListener — CryEngine movie/cutscene event sink
// -----------------------------------------------
// SDK: IMovieSystem.h (global ::IMovieListener). Modeled here as a minimal
// Offsets:: layout replica (like Offsets::I_HUDElementsController) so derived
// wh:: classes (e.g. C_UIEHud) get the correct +0x00 base subobject WITHOUT
// pulling the heavy, interfuscator-tagged IMovieSystem.h into the RE build.
//
// 2 vtable slots only (deleting dtor + OnMovieEvent). The SDK declares this
// <interfuscator:shuffle>, so the relative order of the two slots is NOT
// authoritative — this replica exists ONLY to supply the 8-byte polymorphic
// base; we never call through it.
//
// VERIFIED: C_UIEHud primary vtable 0x1826CDEE0 has exactly 2 slots, and the
// C_UIEHud dtor (sub_18111274C) restores this subobject's vptr to
// IMovieListener::vftable (IDA-labelled). sizeof == 8 (vptr only).

namespace Offsets {

struct IMovieListener {
    enum EMovieEvent { MOVIE_EVENT_START = 0, MOVIE_EVENT_STOP, MOVIE_EVENT_ABORTED };

    virtual void Dtor(char flags) = 0;                                  // [0] 0x00
    virtual void OnMovieEvent(EMovieEvent ev, void* pAnimSequence) = 0;  // [1] 0x08
};

}  // namespace Offsets
