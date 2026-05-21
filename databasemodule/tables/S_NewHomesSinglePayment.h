#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "single_payment"  row_size: 16
// Registration: 0x180146c50
#pragma pack(push, 1)
struct S_NewHomesSinglePayment {
    uint8_t _rowbase[4];  // 0x000
    int32_t single_payment_id;  // 0x004  // PK
    const char* single_payment_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesSinglePayment) == 16, "Size mismatch for S_NewHomesSinglePayment");

}  // namespace wh::databasemodule
