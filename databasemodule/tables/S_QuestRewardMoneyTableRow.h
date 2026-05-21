#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest_reward_money"  row_size: 29
// Registration: 0x1801556e0
#pragma pack(push, 1)
struct S_QuestRewardMoneyTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_reward_money_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* pos;  // 0x008
    uint8_t _pad_0x010[4];
    int32_t objective_id;  // 0x014
    int32_t money_change_id;  // 0x018
    bool is_exclusive;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_QuestRewardMoneyTableRow) == 29, "Size mismatch for S_QuestRewardMoneyTableRow");

}  // namespace wh::databasemodule
