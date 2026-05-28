#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_role"  row_size: 62
// Registration: 0x1801d9dc0
#pragma pack(push, 1)
struct S_SituationRoleTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_role_id;  // 0x010  // PK
    // const char* name;  // 0x010 (alias)
    CryGUID situation_id;  // 0x018
    CryGUID situation_role_condition_id;  // 0x028
    int32_t order_by;  // 0x038
    bool optional;  // 0x03C
    bool passive;  // 0x03D
};
#pragma pack(pop)
static_assert(sizeof(S_SituationRoleTableRow) == 62, "Size mismatch for S_SituationRoleTableRow");

}  // namespace wh::databasemodule
