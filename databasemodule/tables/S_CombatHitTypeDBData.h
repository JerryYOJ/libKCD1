#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_hit_type"  row_size: 24
// Registration: 0x1800d63c0
#pragma pack(push, 1)
struct S_CombatHitTypeDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_hit_type_id;  // 0x004  // PK
    const char* combat_hit_type_name;  // 0x008
    const char* mn_tag;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CombatHitTypeDBData) == 24, "Size mismatch for S_CombatHitTypeDBData");

}  // namespace wh::databasemodule
