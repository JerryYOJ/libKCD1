#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier_effect"  row_size: 8
// Registration: 0x180145390
#pragma pack(push, 1)
struct S_NewHomesModifierEffectResource {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_effect_id;  // 0x004  // PK
    // int32_t resource_id;  // 0x004 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifierEffectResource) == 8, "Size mismatch for S_NewHomesModifierEffectResource");

}  // namespace wh::databasemodule
