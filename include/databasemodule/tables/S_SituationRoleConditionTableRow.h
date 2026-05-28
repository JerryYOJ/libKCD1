#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_role_condition"  row_size: 40
// Registration: 0x1801d9990
#pragma pack(push, 1)
struct S_SituationRoleConditionTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_role_condition_id;  // 0x010  // PK
    // const char* situation_role_condition_name;  // 0x010 (alias)
    int32_t situation_role_condition_type_id;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* situation_role_condition_data;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SituationRoleConditionTableRow) == 40, "Size mismatch for S_SituationRoleConditionTableRow");

}  // namespace wh::databasemodule
