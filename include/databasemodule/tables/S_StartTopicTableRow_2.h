#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "start_topic"  row_size: 22
// Registration: 0x1800e5aa0
#pragma pack(push, 1)
struct S_StartTopicTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t start_topic;  // 0x004  // PK
    int32_t skald_element_id;  // 0x008
    int32_t priority;  // 0x00C
    uint8_t _pad_0x010[4];
    bool allow_greeting;  // 0x014
    bool is_test;  // 0x015
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t branch_type_id;
};
#pragma pack(pop)
static_assert(sizeof(S_StartTopicTableRow_2) == 22, "Size mismatch for S_StartTopicTableRow_2");

}  // namespace wh::databasemodule
