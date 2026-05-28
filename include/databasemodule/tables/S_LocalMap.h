#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ui_local_map"  row_size: 80
// Registration: 0x18010f440
#pragma pack(push, 1)
struct S_LocalMap {
    uint8_t _rowbase[16];  // 0x000
    uint64_t ui_local_map_id;  // 0x010  // PK
    // const char* ui_local_map_name;  // 0x010 (alias)
    float position_x;  // 0x018
    float position_y;  // 0x01C
    float width;  // 0x020
    float height;  // 0x024
    float focus1_x;  // 0x028
    float focus1_y;  // 0x02C
    float focus2_x;  // 0x030
    float focus2_y;  // 0x034
    float major_axis;  // 0x038
    uint8_t _pad_0x03C[4];
    CryGUID location_id;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_LocalMap) == 80, "Size mismatch for S_LocalMap");

}  // namespace wh::databasemodule
