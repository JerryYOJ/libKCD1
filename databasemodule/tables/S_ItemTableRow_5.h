#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 153
// Registration: 0x180102890
#pragma pack(push, 1)
struct S_ItemTableRow_5 {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t item_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    CryGUID clothing_id;  // 0x020
    uint8_t _pad_0x030[16];
    int32_t armor_type_id;  // 0x040
    int32_t armor_subtype_id;  // 0x044
    float slash_def;  // 0x048
    float stab_def;  // 0x04C
    float smash_def;  // 0x050
    float str_req;  // 0x054
    float noise;  // 0x058
    float brightness;  // 0x05C
    float color_hue;  // 0x060
    float color_saturation;  // 0x064
    float zone1_brightness;  // 0x068
    float zone1_hue;  // 0x06C
    float zone1_saturation;  // 0x070
    float zone2_brightness;  // 0x074
    float zone2_hue;  // 0x078
    float zone2_saturation;  // 0x07C
    float zone3_brightness;  // 0x080
    float zone3_hue;  // 0x084
    float zone3_saturation;  // 0x088
    uint8_t _pad_0x08C[4];
    int32_t max_status;  // 0x090
    int32_t superfaction_id;  // 0x094
    bool is_underwear;  // 0x098
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_5) == 153, "Size mismatch for S_ItemTableRow_5");

}  // namespace wh::databasemodule
