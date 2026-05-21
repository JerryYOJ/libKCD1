#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "equipment_part"  row_size: 20
// Registration: 0x1800f3770
#pragma pack(push, 1)
struct S_EquipmentPart {
    uint8_t _rowbase[4];  // 0x000
    int32_t equipment_part_id;  // 0x004  // PK
    const char* equipment_part_name;  // 0x008
    int32_t clothing_adapt_group_id;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_EquipmentPart) == 20, "Size mismatch for S_EquipmentPart");

}  // namespace wh::databasemodule
