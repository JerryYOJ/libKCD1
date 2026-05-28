#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 57
// Registration: 0x180155de0
#pragma pack(push, 1)
struct S_QuestTableRow_5 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // int32_t quest_reward_perk_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* pos;  // 0x008
    uint8_t _pad_0x010[8];
    CryGUID perk_id;  // 0x018
    CryGUID soul_id;  // 0x028
    bool only_unlock;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_5) == 57, "Size mismatch for S_QuestTableRow_5");

}  // namespace wh::databasemodule
