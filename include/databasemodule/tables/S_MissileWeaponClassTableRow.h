#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "missile_weapon_class"  row_size: 8
// Registration: 0x180109550
#pragma pack(push, 1)
struct S_MissileWeaponClassTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t missile_weapon_class_id;  // 0x004  // PK
    // int32_t ammo_class_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_MissileWeaponClassTableRow) == 8, "Size mismatch for S_MissileWeaponClassTableRow");

}  // namespace wh::databasemodule
