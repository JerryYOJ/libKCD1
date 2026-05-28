#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_side"  row_size: 32
// Registration: 0x1800ee4e0
#pragma pack(push, 1)
struct S_ActorSideData {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_side_id;  // 0x004  // PK
    const char* actor_side_name;  // 0x008
    const char* mn_tag;  // 0x010
    float angle_from;  // 0x018
    float angle_to;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_ActorSideData) == 32, "Size mismatch for S_ActorSideData");

}  // namespace wh::databasemodule
