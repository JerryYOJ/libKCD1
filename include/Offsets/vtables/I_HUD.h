#pragma once
#include <cstdint>

// -----------------------------------------------
// I_HUD — HUD-element visibility interface
// -----------------------------------------------
// Warhorse: wh::guimodule::I_HUD (IDA-labelled). Secondary (+0x08) base of
// C_UIEHud. Modeled in Offsets:: for layout reuse, exactly like
// Offsets::I_HUDElementsController. wh:: type -> NOT interfuscated, so slot
// order == declaration order (trust it).
//
// Binary vtable for the C_UIEHud instantiation @ 0x1826CDF58 (5 slots; slot 5
// in a raw dump is the next subobject's COL, not a function). HUD-element
// visibility is a per-element HIDE refcount array (24 ints) that physically
// lives in the DERIVED C_UIEHud at +0x50 (= this+0x48 from the I_HUD
// subobject, which sits at C_UIEHud+0x08). An element is VISIBLE iff its
// hide-count == 0; each AddElementHideRequest raises it, each
// RemoveElementHideRequest lowers it (guarded so it never goes below 0).
//
// Slots (addresses are the C_UIEHud overrides):
//   [0] Dtor                       sub_180B1AE5C  adjustor thunk (this-8) ->
//                                                  C_UIEHud deleting dtor sub_181112944
//   [1] AddElementHideRequest       sub_1804FC270  for each set bit: ++count[bit]
//   [2] RemoveElementHideRequest    sub_1804FC298  for each set bit: if(count[bit]) --count[bit]
//   [3] IsElementVisible            sub_180211D44  returns count[bitIndex(mask)] == 0
//   [4] SetCombatState              sub_1805957E8  writes C_UIEHud+0x174, fires the
//                                                  "SetCombatState" Flash element-function

namespace Offsets {

struct I_HUD {
    virtual void Dtor(char flags) = 0;                         // [0] 0x00
    virtual void AddElementHideRequest(uint32_t mask) = 0;     // [1] 0x08  ++hide-count for each set bit
    virtual void RemoveElementHideRequest(uint32_t mask) = 0;  // [2] 0x10  --hide-count for each set bit
    virtual bool IsElementVisible(uint32_t elementBit) = 0;    // [3] 0x18  hide-count[bitIndex] == 0
    virtual void SetCombatState(int state) = 0;                // [4] 0x20
};

}  // namespace Offsets
