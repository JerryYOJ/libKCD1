#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "credit_layout"  row_size: 16
// Registration: 0x18010e680
#pragma pack(push, 1)
struct S_CreditsLayout {
    uint8_t _rowbase[4];  // 0x000
    int32_t credit_layout_id;  // 0x004  // PK
    const char* credit_layout_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_CreditsLayout) == 16, "Size mismatch for S_CreditsLayout");

}  // namespace wh::databasemodule
