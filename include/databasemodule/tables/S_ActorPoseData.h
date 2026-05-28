#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_pose"  row_size: 40
// Registration: 0x1800ed860
#pragma pack(push, 1)
struct S_ActorPoseData {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_pose_id;  // 0x004  // PK
    const char* actor_pose_name;  // 0x008
    const char* actor_pose_mn_tag;  // 0x010
    const char* actor_pose_opp_mn_tag;  // 0x018
    const char* actor_pose_end_mn_tag;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_ActorPoseData) == 40, "Size mismatch for S_ActorPoseData");

}  // namespace wh::databasemodule
