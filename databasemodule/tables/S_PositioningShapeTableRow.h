#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "positioning_shape"  row_size: 24
// Registration: 0x1801d6360
#pragma pack(push, 1)
struct S_PositioningShapeTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t positioning_shape_id;  // 0x010  // PK
    // const char* positioning_shape_name;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_PositioningShapeTableRow) == 24, "Size mismatch for S_PositioningShapeTableRow");

}  // namespace wh::databasemodule
