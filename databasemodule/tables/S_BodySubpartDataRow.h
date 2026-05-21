#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "body_subpart"  row_size: 32
// Registration: 0x1800fa1e0
#pragma pack(push, 1)
struct S_BodySubpartDataRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t body_subpart_id;  // 0x004  // PK
    const char* body_subpart_name;  // 0x008
    int32_t body_part_id;  // 0x010
    int32_t equipment_part_id;  // 0x014
    float body_subpart_importance;  // 0x018
    float default_relative_charisma;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_BodySubpartDataRow) == 32, "Size mismatch for S_BodySubpartDataRow");

}  // namespace wh::databasemodule
