#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "body_material"  row_size: 24
// Registration: 0x180117410
#pragma pack(push, 1)
struct S_BodyMaterialTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t body_material_id;  // 0x004  // PK
    // int32_t race_id;  // 0x004 (alias)  // PK
    const char* body_material_name;  // 0x008
    int32_t body_subpart_id;  // 0x010
    int32_t blood_zone_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_BodyMaterialTableRow) == 24, "Size mismatch for S_BodyMaterialTableRow");

}  // namespace wh::databasemodule
