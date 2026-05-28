#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "attachment_slot"  row_size: 28
// Registration: 0x1800f20c0
#pragma pack(push, 1)
struct S_AttachmentSlot {
    uint8_t _rowbase[4];  // 0x000
    int32_t attachment_slot_id;  // 0x004  // PK
    const char* attachment_slot_name;  // 0x008
    const char* joint_name;  // 0x010
    int32_t race_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_AttachmentSlot) == 28, "Size mismatch for S_AttachmentSlot");

}  // namespace wh::databasemodule
