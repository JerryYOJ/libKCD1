#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence"  row_size: 60
// Registration: 0x1800e3530
#pragma pack(push, 1)
struct S_SequenceTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_id;  // 0x004  // PK
    // int32_t next;  // 0x004 (alias)
    const char* script;  // 0x008
    int32_t priority;  // 0x010
    uint8_t _pad_0x014[4];
    const char* ui_prompt;  // 0x018
    int32_t group;  // 0x020
    int32_t type;  // 0x024
    int32_t skill_check_difficulty_id;  // 0x028
    int32_t flags;  // 0x02C
    int32_t timeout;  // 0x030
    float speech_coef;  // 0x034
    int32_t reputation;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceTableRow_2) == 60, "Size mismatch for S_SequenceTableRow_2");

}  // namespace wh::databasemodule
