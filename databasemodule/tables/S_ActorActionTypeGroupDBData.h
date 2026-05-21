#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_action_type_group"  row_size: 8
// Registration: 0x1800ed0e0
#pragma pack(push, 1)
struct S_ActorActionTypeGroupDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_action_type_group_id;  // 0x004  // PK
    // int32_t actor_action_type_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ActorActionTypeGroupDBData) == 8, "Size mismatch for S_ActorActionTypeGroupDBData");

}  // namespace wh::databasemodule
