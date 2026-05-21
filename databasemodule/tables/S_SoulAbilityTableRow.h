#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul_ability"  row_size: 24
// Registration: 0x18011ea40
#pragma pack(push, 1)
struct S_SoulAbilityTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t soul_ability_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t perk_id;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SoulAbilityTableRow) == 24, "Size mismatch for S_SoulAbilityTableRow");

}  // namespace wh::databasemodule
