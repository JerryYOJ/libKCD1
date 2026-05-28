#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 68
// Registration: 0x180101fb0
#pragma pack(push, 1)
struct S_ItemTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // CryGUID broken_item_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    const char* inquiver_model;  // 0x020
    const char* inquiver_material;  // 0x028
    int32_t ammo_class_id;  // 0x030
    float slash_att;  // 0x034
    float stab_att;  // 0x038
    float smash_att;  // 0x03C
    float power_mod;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_4) == 68, "Size mismatch for S_ItemTableRow_4");

}  // namespace wh::databasemodule
