#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skill"  row_size: 28
// Registration: 0x180119370
#pragma pack(push, 1)
struct S_DocumentRequiredSkill {
    uint8_t _rowbase[4];  // 0x000
    int32_t skill_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t item_id;  // 0x010  // PK
    // int32_t skill_level_required;  // 0x014 (alias)
    int32_t skill_xp_gained;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_DocumentRequiredSkill) == 28, "Size mismatch for S_DocumentRequiredSkill");

}  // namespace wh::databasemodule
