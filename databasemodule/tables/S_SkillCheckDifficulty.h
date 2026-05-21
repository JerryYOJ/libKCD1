#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skill_check_difficulty"  row_size: 28
// Registration: 0x1801225e0
#pragma pack(push, 1)
struct S_SkillCheckDifficulty {
    uint8_t _rowbase[4];  // 0x000
    int32_t skill_check_difficulty_id;  // 0x004  // PK
    const char* skill_check_difficulty_name;  // 0x008
    int32_t speech_difference;  // 0x010
    float badassness_difference;  // 0x014
    int32_t charisma_difference;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_SkillCheckDifficulty) == 28, "Size mismatch for S_SkillCheckDifficulty");

}  // namespace wh::databasemodule
