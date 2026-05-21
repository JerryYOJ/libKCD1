#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_tag"  row_size: 24
// Registration: 0x1800ea8d0
#pragma pack(push, 1)
struct S_ActionTagMappingData {
    uint8_t _rowbase[8];  // 0x000
    const char* mn_tag;  // 0x008  // PK
    // bool global;  // 0x008 (alias)
    // int32_t priority;  // 0x00C (alias)
    int32_t actor_pose_id;  // 0x010
    int32_t actor_activity_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_ActionTagMappingData) == 24, "Size mismatch for S_ActionTagMappingData");

}  // namespace wh::databasemodule
