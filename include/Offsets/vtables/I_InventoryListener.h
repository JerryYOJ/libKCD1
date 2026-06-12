#pragma once
#include <cstdint>

// -----------------------------------------------
// I_InventoryListener — Binary vtable order (wh:: type, NOT shuffled)
// -----------------------------------------------
// Warhorse: wh::entitymodule::I_InventoryListener
// RTTI: .?AVI_InventoryListener@entitymodule@wh@@
// Modeled in Offsets:: for layout reuse (same approach as I_LocationListener).
//
// Binary vtable for wh::guimodule::C_UIInventoryActions (+0x08 subobject)
// @ 0x1822e89c8 (4 slots):
//   [0] sub_1811351B4  (adjustor; presumed deleting dtor — UNVERIFIED name)
//   [1] sub_181135724
//   [2] sub_1811351BC  \ same COMDAT-folded impl for both slots
//   [3] sub_1811351BC  /
// Slots [1]-[3] are most likely the inventory change notifications that feed
// the "OnItemAdded"/"OnItemRemoved" InventoryActions flash events, but the
// slot->name mapping is UNVERIFIED — kept as _vfN.

namespace Offsets {

struct I_InventoryListener {
    virtual void Dtor(char flags) = 0;  // [0] 0x00  sub_1811351B4 (name UNVERIFIED)
    virtual void _vf1() = 0;            // [1] 0x08  sub_181135724
    virtual void _vf2() = 0;            // [2] 0x10  sub_1811351BC
    virtual void _vf3() = 0;            // [3] 0x18  sub_1811351BC
};

}  // namespace Offsets
