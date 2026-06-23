#pragma once

// -----------------------------------------------
// IViewSystem — CryEngine view-system interface (CViewSystem primary base @ +0x00).
// -----------------------------------------------
// PARTIAL: modeled only enough to position CViewSystem's sibling bases. The
// interface is <interfuscator:shuffle>, so the full binary slot map is not
// reversed here. Known slot (by address): IsPlayingCutScene = vtable slot 19
// (sub_181AAE400, returns *(CViewSystem+0x70) != 0). Primary vtable @ RVA 0x2766CF8.

namespace Offsets {

struct IViewSystem {
    virtual ~IViewSystem() {}   // [0] gives the +0x00 subobject its vptr (real vtable ~20+ slots)
};

}  // namespace Offsets
