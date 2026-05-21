#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skill"  row_size: 24
// Registration: 0x180138390
#pragma pack(push, 1)
struct S_SkillTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t skill_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t soul_id;  // 0x010  // PK
    // int32_t value;  // 0x014 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_SkillTableRow) == 24, "Size mismatch for S_SkillTableRow");

}  // namespace wh::databasemodule
