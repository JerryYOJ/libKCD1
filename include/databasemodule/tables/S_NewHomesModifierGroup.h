#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier_group"  row_size: 16
// Registration: 0x180145cf0
#pragma pack(push, 1)
struct S_NewHomesModifierGroup {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_group_id;  // 0x004  // PK
    const char* modifier_group_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifierGroup) == 16, "Size mismatch for S_NewHomesModifierGroup");

}  // namespace wh::databasemodule
