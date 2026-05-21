#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "body_part"  row_size: 56
// Registration: 0x1800f9b30
#pragma pack(push, 1)
struct S_BodyPartDataRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t body_part_id;  // 0x004  // PK
    const char* body_part_name;  // 0x008
    float body_damage_coeff;  // 0x010
    int32_t race_id;  // 0x014
    const char* mn_tag;  // 0x018
    uint8_t _pad_0x020[16];
    const char* ui_name;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_BodyPartDataRow) == 56, "Size mismatch for S_BodyPartDataRow");

}  // namespace wh::databasemodule
