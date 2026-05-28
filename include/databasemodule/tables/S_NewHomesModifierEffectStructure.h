#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier_effect"  row_size: 24
// Registration: 0x1801455c0
#pragma pack(push, 1)
struct S_NewHomesModifierEffectStructure {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_effect_id;  // 0x004  // PK
    // int32_t structure_id;  // 0x004 (alias)
    int32_t income;  // 0x008
    int32_t people;  // 0x00C
    const char* ui_receiving_effect_desc;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifierEffectStructure) == 24, "Size mismatch for S_NewHomesModifierEffectStructure");

}  // namespace wh::databasemodule
