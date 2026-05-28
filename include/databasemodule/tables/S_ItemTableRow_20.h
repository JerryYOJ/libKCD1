#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 28
// Registration: 0x180109ae0
#pragma pack(push, 1)
struct S_ItemTableRow_20 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // int32_t manipulation_type;  // 0x010 (alias)
    // int32_t npc_tool_type_id;  // 0x014 (alias)
    int32_t npc_tool_subtype_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_20) == 28, "Size mismatch for S_ItemTableRow_20");

}  // namespace wh::databasemodule
