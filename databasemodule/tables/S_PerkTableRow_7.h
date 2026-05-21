#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 24
// Registration: 0x18011e5e0
#pragma pack(push, 1)
struct S_PerkTableRow_7 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // int32_t recipe_id;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_7) == 24, "Size mismatch for S_PerkTableRow_7");

}  // namespace wh::databasemodule
