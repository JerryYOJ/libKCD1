#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "achievement"  row_size: 24
// Registration: 0x180116920
#pragma pack(push, 1)
struct S_AchievementRule {
    uint8_t _rowbase[4];  // 0x000
    int32_t achievement_id;  // 0x004  // PK
    // int32_t statistic_id;  // 0x004 (alias)  // PK
    const char* achievement_rule_name;  // 0x008
    float threshold;  // 0x010
    int32_t achievement_rule_action_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_AchievementRule) == 24, "Size mismatch for S_AchievementRule");

}  // namespace wh::databasemodule
