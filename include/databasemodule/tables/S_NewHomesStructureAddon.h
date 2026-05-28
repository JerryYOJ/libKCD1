#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure_addon"  row_size: 88
// Registration: 0x1801473b0
#pragma pack(push, 1)
struct S_NewHomesStructureAddon {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_addon_id;  // 0x004  // PK
    // int32_t structure_id;  // 0x004 (alias)
    int32_t required_tier;  // 0x008
    int32_t cost;  // 0x00C
    int32_t structure_addon_group_id;  // 0x010
    uint8_t _pad_0x014[4];
    const char* layer_profile;  // 0x018
    const char* ui_name;  // 0x020
    const char* ui_icon;  // 0x028
    bool clear_parcel;  // 0x030
    uint8_t _pad_0x031[7];
    const char* structure_addon_name;  // 0x038
    int32_t ui_order;  // 0x040
    uint8_t _pad_0x044[4];
    const char* cutscene;  // 0x048
    const char* tutorial;  // 0x050
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureAddon) == 88, "Size mismatch for S_NewHomesStructureAddon");

}  // namespace wh::databasemodule
