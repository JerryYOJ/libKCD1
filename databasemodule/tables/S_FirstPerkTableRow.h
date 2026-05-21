#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "first_perk"  row_size: 24
// Registration: 0x18011c3e0
#pragma pack(push, 1)
struct S_FirstPerkTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t first_perk_id;  // 0x010  // PK
    // uint64_t second_perk_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_FirstPerkTableRow) == 24, "Size mismatch for S_FirstPerkTableRow");

}  // namespace wh::databasemodule
