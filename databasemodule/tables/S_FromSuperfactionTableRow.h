#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "from_superfaction"  row_size: 12
// Registration: 0x180125e90
#pragma pack(push, 1)
struct S_FromSuperfactionTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t from_superfaction_id;  // 0x004  // PK
    // int32_t to_superfaction_id;  // 0x004 (alias)  // PK
    float relationship;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_FromSuperfactionTableRow) == 12, "Size mismatch for S_FromSuperfactionTableRow");

}  // namespace wh::databasemodule
