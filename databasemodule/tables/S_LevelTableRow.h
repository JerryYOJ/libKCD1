#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "level"  row_size: 48
// Registration: 0x1800af250
#pragma pack(push, 1)
struct S_LevelTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t level_id;  // 0x004  // PK
    const char* level_name;  // 0x008
    bool keeps_nested_savegame;  // 0x010
    uint8_t _pad_0x011[7];
    const char* level_change_movie;  // 0x018
    int32_t loading_screen_id;  // 0x020
    uint8_t _pad_0x024[4];
    const char* inventory_patch_suffix;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_LevelTableRow) == 48, "Size mismatch for S_LevelTableRow");

}  // namespace wh::databasemodule
