#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "src_action_type"  row_size: 8
// Registration: 0x1800b0250
#pragma pack(push, 1)
struct S_SrcActionTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t src_action_type_id;  // 0x004  // PK
    // int32_t dst_action_type_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SrcActionTypeTableRow) == 8, "Size mismatch for S_SrcActionTypeTableRow");

}  // namespace wh::databasemodule
