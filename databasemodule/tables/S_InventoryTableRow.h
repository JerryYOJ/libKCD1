#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "inventory"  row_size: 24
// Registration: 0x1800fca80
#pragma pack(push, 1)
struct S_InventoryTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t inventory_id;  // 0x010  // PK
    // uint64_t inventory_preset_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_InventoryTableRow) == 24, "Size mismatch for S_InventoryTableRow");

}  // namespace wh::databasemodule
