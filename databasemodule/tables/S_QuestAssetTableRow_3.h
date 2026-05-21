#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest_asset"  row_size: 32
// Registration: 0x180152840
#pragma pack(push, 1)
struct S_QuestAssetTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_asset_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    CryGUID soul_id;  // 0x008
    int32_t soul_class_id;  // 0x018
    int32_t soul_faction_id;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_QuestAssetTableRow_3) == 32, "Size mismatch for S_QuestAssetTableRow_3");

}  // namespace wh::databasemodule
