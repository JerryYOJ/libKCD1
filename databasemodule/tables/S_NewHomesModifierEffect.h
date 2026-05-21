#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier_effect"  row_size: 32
// Registration: 0x180144eb0
#pragma pack(push, 1)
struct S_NewHomesModifierEffect {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_effect_id;  // 0x004  // PK
    // int32_t modifier_effect_type_id;  // 0x004 (alias)
    const char* ui_providing_effect_desc;  // 0x008
    uint8_t _pad_0x010[8];
    const char* modifier_effect_name;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifierEffect) == 32, "Size mismatch for S_NewHomesModifierEffect");

}  // namespace wh::databasemodule
