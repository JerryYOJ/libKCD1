#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_riposte_chain"  row_size: 28
// Registration: 0x1800d6f90
#pragma pack(push, 1)
struct S_CombatRiposteChainStepTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_riposte_chain_id;  // 0x004  // PK
    // int32_t step;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t defense_combat_zone_id;  // 0x00C
    int32_t atk_combat_zone_id;  // 0x010
    int32_t attack_type_id;  // 0x014
    int32_t actor_index;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_CombatRiposteChainStepTableRow) == 28, "Size mismatch for S_CombatRiposteChainStepTableRow");

}  // namespace wh::databasemodule
