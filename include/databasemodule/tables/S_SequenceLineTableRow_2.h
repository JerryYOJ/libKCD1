#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence_line"  row_size: 40
// Registration: 0x1800e1b10
#pragma pack(push, 1)
struct S_SequenceLineTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_line_id;  // 0x004  // PK
    const char* flowchart_name;  // 0x008
    const char* param1;  // 0x010
    const char* param2;  // 0x018
    const char* param3;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceLineTableRow_2) == 40, "Size mismatch for S_SequenceLineTableRow_2");

}  // namespace wh::databasemodule
