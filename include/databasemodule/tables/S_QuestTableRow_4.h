#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 45
// Registration: 0x180155040
#pragma pack(push, 1)
struct S_QuestTableRow_4 {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // bool is_immediate;  // 0x004 (alias)
    const char* pos;  // 0x008
    uint8_t _pad_0x010[28];
    bool is_exclusive;  // 0x02C
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow_4) == 45, "Size mismatch for S_QuestTableRow_4");

}  // namespace wh::databasemodule
