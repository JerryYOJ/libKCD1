#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest_asset"  row_size: 40
// Registration: 0x1801521b0
#pragma pack(push, 1)
struct S_QuestAssetTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_asset_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    CryGUID item_id;  // 0x008
    float min_health;  // 0x018
    int32_t item_category_id;  // 0x01C
    int32_t item_category_type_id;  // 0x020
    int32_t item_category_subtype_id;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_QuestAssetTableRow_2) == 40, "Size mismatch for S_QuestAssetTableRow_2");

}  // namespace wh::databasemodule
