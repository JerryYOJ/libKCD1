#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "se_condition_type"  row_size: 16
// Registration: 0x1801d1400
#pragma pack(push, 1)
struct S_SeConditionTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t se_condition_type_id;  // 0x004  // PK
    const char* se_condition_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SeConditionTypeTableRow) == 16, "Size mismatch for S_SeConditionTypeTableRow");

}  // namespace wh::databasemodule
