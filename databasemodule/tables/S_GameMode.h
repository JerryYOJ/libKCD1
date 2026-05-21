#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "game_mode"  row_size: 16
// Registration: 0x1801fb4f0
#pragma pack(push, 1)
struct S_GameMode {
    uint8_t _rowbase[4];  // 0x000
    int32_t game_mode_id;  // 0x004  // PK
    const char* game_mode_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_GameMode) == 16, "Size mismatch for S_GameMode");

}  // namespace wh::databasemodule
