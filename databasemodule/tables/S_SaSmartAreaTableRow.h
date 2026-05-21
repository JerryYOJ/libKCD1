#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sa_smart_area"  row_size: 36
// Registration: 0x1801dad20
#pragma pack(push, 1)
struct S_SaSmartAreaTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t sa_smart_area_id;  // 0x010  // PK
    // uint64_t sa_behaviour_tag_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    int32_t priority;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SaSmartAreaTableRow) == 36, "Size mismatch for S_SaSmartAreaTableRow");

}  // namespace wh::databasemodule
