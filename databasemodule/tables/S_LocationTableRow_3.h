#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "location"  row_size: 52
// Registration: 0x180129840
#pragma pack(push, 1)
struct S_LocationTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t location_id;  // 0x010  // PK
    // int32_t location_category_id;  // 0x010 (alias)
    const char* location_name;  // 0x018
    int32_t mark_type;  // 0x020
    uint8_t _pad_0x024[4];
    const char* discovery_msg;  // 0x028
    int32_t compass_mark_type_id;  // 0x030
    // --- virtual columns (offset=-1, not in struct memory) ---
    // uint64_t associated_codex_perk_id;
    // uint64_t associated_poi_type_id;
};
#pragma pack(pop)
static_assert(sizeof(S_LocationTableRow_3) == 52, "Size mismatch for S_LocationTableRow_3");

}  // namespace wh::databasemodule
