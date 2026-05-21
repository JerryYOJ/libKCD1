#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 16
// Registration: 0x180156d50
#pragma pack(push, 1)
struct S_QuestTableRow_6 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* script;  // 0x008  // PK
    // const char* pos;  // 0x008 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_6) == 16, "Size mismatch for S_QuestTableRow_6");

}  // namespace wh::databasemodule
