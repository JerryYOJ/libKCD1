#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 8
// Registration: 0x180158670
#pragma pack(push, 1)
struct S_QuestTableRow_7 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t quest_npc_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_7) == 8, "Size mismatch for S_QuestTableRow_7");

}  // namespace wh::databasemodule
