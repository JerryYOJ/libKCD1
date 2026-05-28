#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 36
// Registration: 0x180119be0
#pragma pack(push, 1)
struct S_DocumentRewardPerk {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // uint64_t perk_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    float progress_that_gives_the_perk;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_DocumentRewardPerk) == 36, "Size mismatch for S_DocumentRewardPerk");

}  // namespace wh::databasemodule
