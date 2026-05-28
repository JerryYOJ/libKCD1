#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_subchapter"  row_size: 12
// Registration: 0x1801504c0
#pragma pack(push, 1)
struct S_SkaldSubchapter {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_subchapter_id;  // 0x004  // PK
    int32_t quest_level;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldSubchapter) == 12, "Size mismatch for S_SkaldSubchapter");

}  // namespace wh::databasemodule
