#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 24
// Registration: 0x18011d100
#pragma pack(push, 1)
struct S_PerkTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // int32_t combo_id;  // 0x010 (alias)
    // int32_t combo_step_id;  // 0x014 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_4) == 24, "Size mismatch for S_PerkTableRow_4");

}  // namespace wh::databasemodule
