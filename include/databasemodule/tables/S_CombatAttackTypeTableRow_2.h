#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_attack_type"  row_size: 40
// Registration: 0x1800d2f00
#pragma pack(push, 1)
struct S_CombatAttackTypeTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_attack_type_id;  // 0x004  // PK
    const char* combat_attack_type_name;  // 0x008
    int32_t rpg_damage_type_id;  // 0x010
    float relative_stamina_cost;  // 0x014
    const char* mn_tag;  // 0x018
    const char* opp_mn_tag;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_CombatAttackTypeTableRow_2) == 40, "Size mismatch for S_CombatAttackTypeTableRow_2");

}  // namespace wh::databasemodule
