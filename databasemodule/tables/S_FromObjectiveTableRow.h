#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "from_objective"  row_size: 13
// Registration: 0x180157280
#pragma pack(push, 1)
struct S_FromObjectiveTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t from_objective_id;  // 0x004  // PK
    // int32_t to_objective_id;  // 0x004 (alias)  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    bool enabled;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_FromObjectiveTableRow) == 13, "Size mismatch for S_FromObjectiveTableRow");

}  // namespace wh::databasemodule
