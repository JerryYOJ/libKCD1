#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "poi_type"  row_size: 24
// Registration: 0x18011b870
#pragma pack(push, 1)
struct S_PoiTypeTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t poi_type_id;  // 0x010  // PK
    // uint64_t perk_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_PoiTypeTableRow) == 24, "Size mismatch for S_PoiTypeTableRow");

}  // namespace wh::databasemodule
