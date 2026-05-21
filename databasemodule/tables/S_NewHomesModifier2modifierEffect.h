#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier"  row_size: 8
// Registration: 0x1801446d0
#pragma pack(push, 1)
struct S_NewHomesModifier2modifierEffect {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_id;  // 0x004  // PK
    // int32_t modifier_effect_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifier2modifierEffect) == 8, "Size mismatch for S_NewHomesModifier2modifierEffect");

}  // namespace wh::databasemodule
