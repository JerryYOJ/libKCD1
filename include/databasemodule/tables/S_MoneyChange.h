#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "money_change"  row_size: 8
// Registration: 0x18014f1d0
#pragma pack(push, 1)
struct S_MoneyChange {
    uint8_t _rowbase[4];  // 0x000
    int32_t money_change_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_MoneyChange) == 8, "Size mismatch for S_MoneyChange");

}  // namespace wh::databasemodule
