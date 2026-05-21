#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 32
// Registration: 0x18011c840
#pragma pack(push, 1)
struct S_PerkTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // CryGUID source_buff_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_2) == 32, "Size mismatch for S_PerkTableRow_2");

}  // namespace wh::databasemodule
