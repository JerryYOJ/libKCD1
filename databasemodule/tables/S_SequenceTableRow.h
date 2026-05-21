#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence"  row_size: 32
// Registration: 0x1800e2f20
#pragma pack(push, 1)
struct S_SequenceTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_id;  // 0x004  // PK
    // int32_t order_by;  // 0x004 (alias)  // PK
    int32_t objective_id;  // 0x008
    int32_t action;  // 0x00C
    uint8_t _pad_0x010[8];
    const char* condition;  // 0x018
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t quest_id;
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceTableRow) == 32, "Size mismatch for S_SequenceTableRow");

}  // namespace wh::databasemodule
