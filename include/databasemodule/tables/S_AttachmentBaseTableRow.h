#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "attachment_base"  row_size: 76
// Registration: 0x1800f6ff0
#pragma pack(push, 1)
struct S_AttachmentBaseTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t attachment_base_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* attachment_base_name;  // 0x020
    int32_t race_id;  // 0x028
    int32_t gender_id;  // 0x02C
    const char* model;  // 0x030
    const char* material;  // 0x038
    float lod_persistence;  // 0x040
    uint8_t _pad_0x044[4];
    int32_t attachment_slot_id;  // 0x048
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_AttachmentBaseTableRow) == 76, "Size mismatch for S_AttachmentBaseTableRow");

}  // namespace wh::databasemodule
