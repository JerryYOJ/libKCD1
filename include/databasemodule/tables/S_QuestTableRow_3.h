#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 24
// Registration: 0x180154a20
#pragma pack(push, 1)
struct S_QuestTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* rpg_attr;  // 0x008  // PK
    // const char* pos;  // 0x008 (alias)
    uint8_t _pad_0x010[4];
    int32_t exp_change_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_3) == 24, "Size mismatch for S_QuestTableRow_3");

}  // namespace wh::databasemodule
