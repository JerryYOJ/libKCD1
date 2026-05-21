#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 32
// Registration: 0x180108d10
#pragma pack(push, 1)
struct S_ItemTableRow_17 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float attack;  // 0x010 (alias)
    // float slash_att_mod;  // 0x014 (alias)
    float stab_att_mod;  // 0x018
    float smash_att_mod;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_17) == 32, "Size mismatch for S_ItemTableRow_17");

}  // namespace wh::databasemodule
