#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "inventory_preset"  row_size: 32
// Registration: 0x1800fd980
#pragma pack(push, 1)
struct S_InventoryPresetTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t inventory_preset_id;  // 0x010  // PK
    // const char* inventory_preset_name;  // 0x010 (alias)
    bool read_only;  // 0x018
    uint8_t _pad_0x019[3];
    float restock_interval;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_InventoryPresetTableRow) == 32, "Size mismatch for S_InventoryPresetTableRow");

}  // namespace wh::databasemodule
