#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "credit_people"  row_size: 24
// Registration: 0x18010e8b0
#pragma pack(push, 1)
struct S_CreditPeopleTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t credit_people_id;  // 0x004  // PK
    const char* credit_people_name;  // 0x008
    int32_t credit_role_id;  // 0x010
    int32_t order_by;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_CreditPeopleTableRow) == 24, "Size mismatch for S_CreditPeopleTableRow");

}  // namespace wh::databasemodule
