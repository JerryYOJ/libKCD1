#pragma once
#include <cstdint>

// -----------------------------------------------
// I_EquipmentManagerListener — Binary vtable order (wh:: type, NOT shuffled)
// -----------------------------------------------
// Warhorse: wh::entitymodule::I_EquipmentManagerListener
// RTTI: .?AVI_EquipmentManagerListener@entitymodule@wh@@
// Modeled in Offsets:: for layout reuse (same approach as I_LocationListener).
//
// Binary vtable for wh::guimodule::C_UIInventoryActions (+0x10 subobject)
// @ 0x1822e89f0 (3 slots):
//   [0] sub_180B1AF10        deleting-dtor adjustor thunk (this -= 0x10)
//   [1] _guard_check_icall_nop  (empty default)
//   [2] _guard_check_icall_nop  (empty default)
// Slot->name mapping beyond [0] UNVERIFIED — kept as _vfN.

namespace Offsets {

struct I_EquipmentManagerListener {
    virtual void Dtor(char flags) = 0;  // [0] 0x00
    virtual void _vf1() = 0;            // [1] 0x08  nop
    virtual void _vf2() = 0;            // [2] 0x10  nop
};

}  // namespace Offsets
