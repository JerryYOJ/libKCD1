#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ui_map_label"  row_size: 48
// Registration: 0x180111900
#pragma pack(push, 1)
struct S_UiMapLabelTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t ui_map_label_id;  // 0x010  // PK
    // CryGUID location_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    float position_x;  // 0x020
    float position_y;  // 0x024
    const char* ui_name;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_UiMapLabelTableRow) == 48, "Size mismatch for S_UiMapLabelTableRow");

}  // namespace wh::databasemodule
