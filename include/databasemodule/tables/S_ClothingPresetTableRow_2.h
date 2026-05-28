#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "clothing_preset"  row_size: 24
// Registration: 0x1800f6da0
#pragma pack(push, 1)
struct S_ClothingPresetTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t clothing_preset_id;  // 0x010  // PK
    // uint64_t armor_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ClothingPresetTableRow_2) == 24, "Size mismatch for S_ClothingPresetTableRow_2");

}  // namespace wh::databasemodule
