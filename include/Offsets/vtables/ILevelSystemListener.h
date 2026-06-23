#pragma once

// -----------------------------------------------
// ILevelSystemListener — CryEngine level-system listener (CViewSystem base @ +0x10).
// -----------------------------------------------
// RTTI-confirmed 3rd base of CViewSystem (.?AUILevelSystemListener@@). PARTIAL:
// modeled only to position the layout; slot map not reversed. Vtable @ RVA 0x2766CA0.

namespace Offsets {

struct ILevelSystemListener {
    virtual ~ILevelSystemListener() {}   // [0] gives the +0x10 subobject its vptr
};

}  // namespace Offsets
