#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "link_name"  row_size: 72
// Registration: 0x1800fb650
#pragma pack(push, 1)
struct S_LinkNameTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    // const char* link_name;  // 0x008 (alias)  // PK
    const char* level_name;  // 0x010
    // uint64_t entity_id;  // 0x010 (alias)  // PK
    // uint64_t target_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[16];
    const char* entity_name;  // 0x028
    uint8_t _pad_0x030[16];
    const char* target_name;  // 0x040
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_LinkNameTableRow) == 72, "Size mismatch for S_LinkNameTableRow");

}  // namespace wh::databasemodule
