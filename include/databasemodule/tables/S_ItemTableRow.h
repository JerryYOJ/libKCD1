#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 104
// Registration: 0x1800f4180
#pragma pack(push, 1)
struct S_ItemTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // uint64_t clothing_attachment_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    float brightness;  // 0x020
    float color_hue;  // 0x024
    float color_saturation;  // 0x028
    float zone1_brightness;  // 0x02C
    float zone1_hue;  // 0x030
    float zone1_saturation;  // 0x034
    float zone2_brightness;  // 0x038
    float zone2_hue;  // 0x03C
    float zone2_saturation;  // 0x040
    float zone3_brightness;  // 0x044
    float zone3_hue;  // 0x048
    float zone3_saturation;  // 0x04C
    uint8_t _pad_0x050[8];
    const char* computer_name;  // 0x058
    const char* timestamp;  // 0x060
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow) == 104, "Size mismatch for S_ItemTableRow");

}  // namespace wh::databasemodule
