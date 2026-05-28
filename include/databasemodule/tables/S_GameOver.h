#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "game_over"  row_size: 16
// Registration: 0x180144020
#pragma pack(push, 1)
struct S_GameOver {
    uint8_t _rowbase[4];  // 0x000
    int32_t game_over_id;  // 0x004  // PK
    const char* game_over_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_GameOver) == 16, "Size mismatch for S_GameOver");

}  // namespace wh::databasemodule
