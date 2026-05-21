#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "achievement"  row_size: 64
// Registration: 0x180116220
#pragma pack(push, 1)
struct S_Achievement {
    uint8_t _rowbase[4];  // 0x000
    int32_t achievement_id;  // 0x004  // PK
    const char* achievement_name;  // 0x008
    int32_t trophy_id;  // 0x010
    uint8_t _pad_0x014[4];
    const char* xboxlive_id;  // 0x018
    bool unlock_on_steam;  // 0x020
    uint8_t _pad_0x021[7];
    const char* mstore_id;  // 0x028
    int32_t origin_id;  // 0x030
    uint8_t _pad_0x034[4];
    const char* gog_id;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_Achievement) == 64, "Size mismatch for S_Achievement");

}  // namespace wh::databasemodule
