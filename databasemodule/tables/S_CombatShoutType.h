#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_shout_type"  row_size: 28
// Registration: 0x180118ab0
#pragma pack(push, 1)
struct S_CombatShoutType {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_shout_type_id;  // 0x004  // PK
    const char* combat_shout_type_name;  // 0x008
    int32_t metarole_id;  // 0x010
    float period;  // 0x014
    float period_rnd_spread;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_CombatShoutType) == 28, "Size mismatch for S_CombatShoutType");

}  // namespace wh::databasemodule
