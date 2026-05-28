#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_action_trigger"  row_size: 20
// Registration: 0x1800d1b20
#pragma pack(push, 1)
struct S_CombatActionTriggerDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_action_trigger_id;  // 0x004  // PK
    // int32_t combat_guard_type_id;  // 0x004 (alias)
    int32_t combat_input_class_id;  // 0x008
    float timeout;  // 0x00C
    int32_t combat_action_type_id;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CombatActionTriggerDBData) == 20, "Size mismatch for S_CombatActionTriggerDBData");

}  // namespace wh::databasemodule
