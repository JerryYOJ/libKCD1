#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier_effect_type"  row_size: 16
// Registration: 0x180145ac0
#pragma pack(push, 1)
struct S_NewHomesModifierEffectType {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_effect_type_id;  // 0x004  // PK
    const char* modifier_effect_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifierEffectType) == 16, "Size mismatch for S_NewHomesModifierEffectType");

}  // namespace wh::databasemodule
