#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "clothing_preset"  row_size: 53
// Registration: 0x1800fa7d0
#pragma pack(push, 1)
struct S_ClothingPresetTableRow_3 {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t clothing_preset_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* clothing_preset_name;  // 0x020
    int32_t social_class_id;  // 0x028
    int32_t wealth_level;  // 0x02C
    int32_t gender_id;  // 0x030
    bool prefers_hood_on;  // 0x034
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_ClothingPresetTableRow_3) == 53, "Size mismatch for S_ClothingPresetTableRow_3");

}  // namespace wh::databasemodule
