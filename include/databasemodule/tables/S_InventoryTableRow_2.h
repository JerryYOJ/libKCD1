#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "inventory"  row_size: 32
// Registration: 0x1800fcdb0
#pragma pack(push, 1)
struct S_InventoryTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t inventory_id;  // 0x010  // PK
    // const char* inventory_name;  // 0x010 (alias)
    bool read_only;  // 0x018
    uint8_t _pad_0x019[3];
    float restock_interval;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_InventoryTableRow_2) == 32, "Size mismatch for S_InventoryTableRow_2");

}  // namespace wh::databasemodule
