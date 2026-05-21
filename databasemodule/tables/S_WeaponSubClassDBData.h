#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "weapon_sub_class"  row_size: 16
// Registration: 0x180100e80
#pragma pack(push, 1)
struct S_WeaponSubClassDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t weapon_sub_class_id;  // 0x004  // PK
    const char* weapon_sub_class_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_WeaponSubClassDBData) == 16, "Size mismatch for S_WeaponSubClassDBData");

}  // namespace wh::databasemodule
