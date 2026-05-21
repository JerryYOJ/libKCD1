#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "poi_type"  row_size: 76
// Registration: 0x1801374a0
#pragma pack(push, 1)
struct S_PoiTypeTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t poi_type_id;  // 0x010  // PK
    // int32_t mark_type;  // 0x010 (alias)
    const char* label;  // 0x018
    const char* discovery_msg;  // 0x020
    float discovery_dist;  // 0x028
    int32_t compass_mark_type_id;  // 0x02C
    uint8_t _pad_0x030[16];
    int32_t discovery_msg_mode;  // 0x040
    bool discoverable_by_location;  // 0x044
    uint8_t _pad_0x045[3];
    int32_t ui_order;  // 0x048
};
#pragma pack(pop)
static_assert(sizeof(S_PoiTypeTableRow_4) == 76, "Size mismatch for S_PoiTypeTableRow_4");

}  // namespace wh::databasemodule
