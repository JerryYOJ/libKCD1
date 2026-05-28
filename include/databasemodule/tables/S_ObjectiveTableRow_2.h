#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "objective"  row_size: 36
// Registration: 0x180157f10
#pragma pack(push, 1)
struct S_ObjectiveTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t objective_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t count;  // 0x00C
    uint8_t _pad_0x010[4];
    int32_t user_id;  // 0x014
    uint8_t _pad_0x018[8];
    int32_t map_asset_id;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_ObjectiveTableRow_2) == 36, "Size mismatch for S_ObjectiveTableRow_2");

}  // namespace wh::databasemodule
