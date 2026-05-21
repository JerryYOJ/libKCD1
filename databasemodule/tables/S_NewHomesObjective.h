#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "objective"  row_size: 36
// Registration: 0x180145f20
#pragma pack(push, 1)
struct S_NewHomesObjective {
    uint8_t _rowbase[4];  // 0x000
    int32_t objective_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    int32_t complete_limit;  // 0x010
    uint8_t _pad_0x014[4];
    const char* ui_description;  // 0x018
    int32_t ui_order;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesObjective) == 36, "Size mismatch for S_NewHomesObjective");

}  // namespace wh::databasemodule
