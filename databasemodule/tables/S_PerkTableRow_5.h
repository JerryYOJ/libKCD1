#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 40
// Registration: 0x18011d420
#pragma pack(push, 1)
struct S_PerkTableRow_5 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    CryGUID forward_perk_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_5) == 40, "Size mismatch for S_PerkTableRow_5");

}  // namespace wh::databasemodule
