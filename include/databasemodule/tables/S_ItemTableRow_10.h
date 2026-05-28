#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 40
// Registration: 0x180106410
#pragma pack(push, 1)
struct S_ItemTableRow_10 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float visibility;  // 0x010 (alias)
    // float conspicuousness;  // 0x014 (alias)
    float charisma;  // 0x018
    uint8_t _pad_0x01C[4];
    int32_t social_class_id;  // 0x020
    int32_t wealth_level;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_10) == 40, "Size mismatch for S_ItemTableRow_10");

}  // namespace wh::databasemodule
