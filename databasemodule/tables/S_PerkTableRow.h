#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 32
// Registration: 0x18011c610
#pragma pack(push, 1)
struct S_PerkTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // CryGUID buff_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow) == 32, "Size mismatch for S_PerkTableRow");

}  // namespace wh::databasemodule
