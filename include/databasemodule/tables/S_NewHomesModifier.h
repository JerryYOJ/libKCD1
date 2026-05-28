#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "modifier"  row_size: 29
// Registration: 0x180144900
#pragma pack(push, 1)
struct S_NewHomesModifier {
    uint8_t _rowbase[4];  // 0x000
    int32_t modifier_id;  // 0x004  // PK
    const char* modifier_name;  // 0x008
    int32_t modifier_group_id;  // 0x010
    bool is_hidden;  // 0x014
    uint8_t _pad_0x015[3];
    int32_t ui_order;  // 0x018
    bool show_notification;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesModifier) == 29, "Size mismatch for S_NewHomesModifier");

}  // namespace wh::databasemodule
