#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure"  row_size: 80
// Registration: 0x180148710
#pragma pack(push, 1)
struct S_NewHomesStructureTier {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_id;  // 0x004  // PK
    // int32_t tier;  // 0x004 (alias)  // PK
    int32_t cost;  // 0x008
    int32_t income;  // 0x00C
    int32_t people;  // 0x010
    uint8_t _pad_0x014[4];
    const char* layer_profile;  // 0x018
    const char* ui_name;  // 0x020
    const char* ui_icon;  // 0x028
    bool hidden_on_map;  // 0x030
    bool hidden_in_book;  // 0x031
    uint8_t _pad_0x032[6];
    const char* cutscene;  // 0x038
    const char* unload_layer_profile;  // 0x040
    const char* ui_description;  // 0x048
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureTier) == 80, "Size mismatch for S_NewHomesStructureTier");

}  // namespace wh::databasemodule
