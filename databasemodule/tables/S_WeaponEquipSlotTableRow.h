#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "weapon_equip_slot"  row_size: 32
// Registration: 0x1801439a0
#pragma pack(push, 1)
struct S_WeaponEquipSlotTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t weapon_equip_slot_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t soul_id;  // 0x010  // PK
    // float health;  // 0x014 (alias)
    float rust;  // 0x018
    float blood;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_WeaponEquipSlotTableRow) == 32, "Size mismatch for S_WeaponEquipSlotTableRow");

}  // namespace wh::databasemodule
