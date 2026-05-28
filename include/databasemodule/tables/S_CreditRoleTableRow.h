#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "credit_role"  row_size: 8
// Registration: 0x18010ecc0
#pragma pack(push, 1)
struct S_CreditRoleTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t credit_role_id;  // 0x004  // PK
    // int32_t language_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CreditRoleTableRow) == 8, "Size mismatch for S_CreditRoleTableRow");

}  // namespace wh::databasemodule
