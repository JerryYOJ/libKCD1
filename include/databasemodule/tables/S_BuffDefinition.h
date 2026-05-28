#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "buff"  row_size: 120
// Registration: 0x180117910
#pragma pack(push, 1)
struct S_BuffDefinition {
    uint8_t _rowbase[16];  // 0x000
    uint64_t buff_id;  // 0x010  // PK
    // const char* buff_name;  // 0x010 (alias)
    const char* buff_desc;  // 0x018
    int32_t buff_class_id;  // 0x020
    int32_t icon_id;  // 0x024
    float duration;  // 0x028
    int32_t buff_exclusivity_id;  // 0x02C
    const char* implementation;  // 0x030
    const char* params;  // 0x038
    const char* buff_ui_name;  // 0x040
    int32_t buff_ui_type_id;  // 0x048
    int32_t buff_ai_tag_id;  // 0x04C
    int32_t buff_ui_order;  // 0x050
    bool is_persistent;  // 0x054
    uint8_t _pad_0x055[3];
    const char* visual_effect;  // 0x058
    int32_t slot_icon_id;  // 0x060
    uint8_t _pad_0x064[4];
    const char* slot_buff_ui_name;  // 0x068
    int32_t buff_lifetime_id;  // 0x070
    int32_t buff_ui_visibility_id;  // 0x074
};
#pragma pack(pop)
static_assert(sizeof(S_BuffDefinition) == 120, "Size mismatch for S_BuffDefinition");

}  // namespace wh::databasemodule
