#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_activity"  row_size: 24
// Registration: 0x1800ed540
#pragma pack(push, 1)
struct S_ActorActivityData {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_activity_id;  // 0x004  // PK
    const char* actor_activity_name;  // 0x008
    const char* actor_activity_mn_tag;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_ActorActivityData) == 24, "Size mismatch for S_ActorActivityData");

}  // namespace wh::databasemodule
