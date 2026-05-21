#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_action_type"  row_size: 120
// Registration: 0x1800eea60
#pragma pack(push, 1)
struct S_ActorActionTypeTableRow_4 {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_action_type_id;  // 0x004
    int32_t actor_action_type_id_request;  // 0x008
    int32_t actor_pose_id;  // 0x00C
    int32_t actor_activity_id;  // 0x010
    int32_t actor_class_hash;  // 0x014
    int32_t actor_end_pose_id;  // 0x018
    uint8_t _pad_0x01C[12];
    const char* mn_fragment_id;  // 0x028
    const char* mn_tags;  // 0x030
    int32_t mn_option_index;  // 0x038
    float animation_duration;  // 0x03C
    int32_t actor_side_id;  // 0x040
    int16_t init_align0;  // 0x044
    int16_t init_align1;  // 0x050
    int16_t init_sec_align0;  // 0x05C
    int16_t init_sec_align1;  // 0x068
    float fade_in;  // 0x074
    // --- virtual columns (offset=-1, not in struct memory) ---
    // bool mounted;
};
#pragma pack(pop)
static_assert(sizeof(S_ActorActionTypeTableRow_4) == 120, "Size mismatch for S_ActorActionTypeTableRow_4");

}  // namespace wh::databasemodule
