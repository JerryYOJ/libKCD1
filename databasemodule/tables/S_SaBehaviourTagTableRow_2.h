#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sa_behaviour_tag"  row_size: 56
// Registration: 0x1801db840
#pragma pack(push, 1)
struct S_SaBehaviourTagTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t sa_behaviour_tag_id;  // 0x010  // PK
    // const char* sa_behaviour_tag_name;  // 0x010 (alias)
    const char* tree_name;  // 0x018
    const char* tree_file;  // 0x020
    int32_t on_leave_action;  // 0x028
    int32_t on_enter_child_action;  // 0x02C
    int32_t on_success_action;  // 0x030
    int32_t on_fail_action;  // 0x034
};
#pragma pack(pop)
static_assert(sizeof(S_SaBehaviourTagTableRow_2) == 56, "Size mismatch for S_SaBehaviourTagTableRow_2");

}  // namespace wh::databasemodule
