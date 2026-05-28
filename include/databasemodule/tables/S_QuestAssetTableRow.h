#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest_asset"  row_size: 12
// Registration: 0x180150f30
#pragma pack(push, 1)
struct S_QuestAssetTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_asset_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    int32_t type;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_QuestAssetTableRow) == 12, "Size mismatch for S_QuestAssetTableRow");

}  // namespace wh::databasemodule
