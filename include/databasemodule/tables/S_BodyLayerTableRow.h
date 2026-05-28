#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "body_layer"  row_size: 24
// Registration: 0x1800f6020
#pragma pack(push, 1)
struct S_BodyLayerTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t body_layer_id;  // 0x004  // PK
    const char* body_layer_name;  // 0x008
    int32_t body_layer_type_id;  // 0x010
    int32_t layer_order;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_BodyLayerTableRow) == 24, "Size mismatch for S_BodyLayerTableRow");

}  // namespace wh::databasemodule
