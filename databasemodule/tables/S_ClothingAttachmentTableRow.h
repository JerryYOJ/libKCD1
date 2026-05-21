#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "clothing_attachment"  row_size: 80
// Registration: 0x1800f8450
#pragma pack(push, 1)
struct S_ClothingAttachmentTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t clothing_attachment_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* clothing_attachment_name;  // 0x020
    int32_t race_id;  // 0x028
    int32_t gender_id;  // 0x02C
    const char* model;  // 0x030
    const char* material;  // 0x038
    float lod_persistence;  // 0x040
    uint8_t _pad_0x044[4];
    int32_t social_class_id;  // 0x048
    int32_t wealth_level;  // 0x04C
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_ClothingAttachmentTableRow) == 80, "Size mismatch for S_ClothingAttachmentTableRow");

}  // namespace wh::databasemodule
