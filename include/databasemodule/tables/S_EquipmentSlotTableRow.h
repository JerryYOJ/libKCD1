#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "equipment_slot"  row_size: 24
// Registration: 0x180143660
#pragma pack(push, 1)
struct S_EquipmentSlotTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t equipment_slot_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t soul_id;  // 0x010  // PK
    // float health;  // 0x014 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_EquipmentSlotTableRow) == 24, "Size mismatch for S_EquipmentSlotTableRow");

}  // namespace wh::databasemodule
