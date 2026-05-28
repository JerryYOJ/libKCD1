#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_behaviour_tag"  row_size: 72
// Registration: 0x1801ddae0
#pragma pack(push, 1)
struct S_SoBehaviourTagTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t so_behaviour_tag_id;  // 0x010  // PK
    // const char* so_behaviour_tag_name;  // 0x010 (alias)
    const char* tree_name;  // 0x018
    const char* tree_file;  // 0x020
    int32_t on_success_action;  // 0x028
    int32_t on_fail_action;  // 0x02C
    int32_t initial_state;  // 0x030
    int32_t max_instances;  // 0x034
    CryGUID condition_id;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_SoBehaviourTagTableRow_3) == 72, "Size mismatch for S_SoBehaviourTagTableRow_3");

}  // namespace wh::databasemodule
