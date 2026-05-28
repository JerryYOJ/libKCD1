#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_attack_type"  row_size: 16
// Registration: 0x1800d2b00
#pragma pack(push, 1)
struct S_CombatAttackHitStatisticsDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_attack_type_id;  // 0x004  // PK
    // int32_t combat_zone_id;  // 0x004 (alias)  // PK
    // int32_t body_subpart_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t hit_count;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_CombatAttackHitStatisticsDBData) == 16, "Size mismatch for S_CombatAttackHitStatisticsDBData");

}  // namespace wh::databasemodule
