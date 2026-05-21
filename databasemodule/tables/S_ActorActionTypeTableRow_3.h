#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_action_type"  row_size: 16
// Registration: 0x1800ed310
#pragma pack(push, 1)
struct S_ActorActionTypeTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_action_type_id;  // 0x004  // PK
    const char* actor_action_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_ActorActionTypeTableRow_3) == 16, "Size mismatch for S_ActorActionTypeTableRow_3");

}  // namespace wh::databasemodule
