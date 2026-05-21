#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 28
// Registration: 0x180109ee0
#pragma pack(push, 1)
struct S_ItemTableRow_21 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float efficiency;  // 0x010 (alias)
    // int32_t ointment_item_type_id;  // 0x014 (alias)
    int32_t ointment_item_subtype_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_21) == 28, "Size mismatch for S_ItemTableRow_21");

}  // namespace wh::databasemodule
