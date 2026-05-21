#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "weapon_preset"  row_size: 24
// Registration: 0x18010d000
#pragma pack(push, 1)
struct S_WeaponPresetTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t weapon_preset_id;  // 0x010  // PK
    // uint64_t item_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_WeaponPresetTableRow) == 24, "Size mismatch for S_WeaponPresetTableRow");

}  // namespace wh::databasemodule
