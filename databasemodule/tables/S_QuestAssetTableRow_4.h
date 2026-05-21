#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest_asset"  row_size: 25
// Registration: 0x1801576b0
#pragma pack(push, 1)
struct S_QuestAssetTableRow_4 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_asset_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    const char* map;  // 0x008
    const char* entity;  // 0x010
    bool show_as_area;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_QuestAssetTableRow_4) == 25, "Size mismatch for S_QuestAssetTableRow_4");

}  // namespace wh::databasemodule
