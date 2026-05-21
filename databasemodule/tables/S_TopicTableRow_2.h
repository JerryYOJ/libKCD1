#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "topic"  row_size: 40
// Registration: 0x1800e87d0
#pragma pack(push, 1)
struct S_TopicTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t topic_id;  // 0x004  // PK
    // int32_t time_limit;  // 0x004 (alias)
    uint8_t _pad_0x008[8];
    const char* label;  // 0x010
    int32_t priority;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* custom_camera;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_TopicTableRow_2) == 40, "Size mismatch for S_TopicTableRow_2");

}  // namespace wh::databasemodule
