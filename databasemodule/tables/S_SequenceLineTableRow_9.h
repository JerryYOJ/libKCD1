#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence_line"  row_size: 16
// Registration: 0x1800e7b50
#pragma pack(push, 1)
struct S_SequenceLineTableRow_9 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_line_id;  // 0x004  // PK
    // int32_t sequence_id;  // 0x004 (alias)
    int32_t order_by;  // 0x008
    int32_t sequence_line_type;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceLineTableRow_9) == 16, "Size mismatch for S_SequenceLineTableRow_9");

}  // namespace wh::databasemodule
