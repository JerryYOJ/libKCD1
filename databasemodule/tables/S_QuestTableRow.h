#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "quest"  row_size: 105
// Registration: 0x180151320
#pragma pack(push, 1)
struct S_QuestTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t quest_id;  // 0x004  // PK
    const char* quest_name;  // 0x008
    const char* long_desc;  // 0x010
    int32_t counter;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* pos1;  // 0x020
    const char* pos2;  // 0x028
    const char* pos3;  // 0x030
    const char* group;  // 0x038
    const char* comment;  // 0x040
    const char* computer_name;  // 0x048
    const char* timestamp;  // 0x050
    const char* smart_object;  // 0x058
    bool is_activated;  // 0x060
    uint8_t _pad_0x061[3];
    int32_t quest_type_id;  // 0x064
    bool is_progress_visible;  // 0x068
};
#pragma pack(pop)
static_assert(sizeof(S_QuestTableRow) == 105, "Size mismatch for S_QuestTableRow");

}  // namespace wh::databasemodule
