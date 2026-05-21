#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "equipment_part"  row_size: 28
// Registration: 0x1800f6430
#pragma pack(push, 1)
struct S_EquipmentPartTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t equipment_part_id;  // 0x004  // PK
    // int32_t body_layer_type_id;  // 0x004 (alias)  // PK
    const char* equipment_slot_name;  // 0x008
    uint8_t _pad_0x010[8];
    int32_t ui_body_part_id;  // 0x018
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t equipment_slot_id;
};
#pragma pack(pop)
static_assert(sizeof(S_EquipmentPartTableRow) == 28, "Size mismatch for S_EquipmentPartTableRow");

}  // namespace wh::databasemodule
