#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 16
// Registration: 0x1801544f0
#pragma pack(push, 1)
struct S_QuestTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // int32_t statistic_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* pos;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_2) == 16, "Size mismatch for S_QuestTableRow_2");

}  // namespace wh::databasemodule
