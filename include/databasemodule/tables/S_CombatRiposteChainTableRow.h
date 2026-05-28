#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_riposte_chain"  row_size: 40
// Registration: 0x1800d75c0
#pragma pack(push, 1)
struct S_CombatRiposteChainTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_riposte_chain_id;  // 0x004  // PK
    const char* combat_riposte_chain_strid;  // 0x008
    const char* combat_riposte_chain_name;  // 0x010
    int32_t atk_r_weapon_class_id;  // 0x018
    int32_t atk_l_weapon_class_id;  // 0x01C
    int32_t blk_r_weapon_class_id;  // 0x020
    int32_t blk_l_weapon_class_id;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_CombatRiposteChainTableRow) == 40, "Size mismatch for S_CombatRiposteChainTableRow");

}  // namespace wh::databasemodule
