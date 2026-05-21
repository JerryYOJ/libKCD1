#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "faction"  row_size: 49
// Registration: 0x180119f00
#pragma pack(push, 1)
struct S_Faction {
    uint8_t _rowbase[4];  // 0x000
    int32_t faction_id;  // 0x004  // PK
    const char* faction_name;  // 0x008
    const char* description;  // 0x010
    float player_reputation;  // 0x018
    int32_t superfaction_id;  // 0x01C
    uint8_t _pad_0x020[16];
    bool visible;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_Faction) == 49, "Size mismatch for S_Faction");

}  // namespace wh::databasemodule
