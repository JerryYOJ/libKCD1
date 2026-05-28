#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "timestamp"  row_size: 44
// Registration: 0x18015a790
#pragma pack(push, 1)
struct S_TimestampTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    const char* level_name;  // 0x010
    uint8_t _pad_0x018[16];
    int32_t shop_id;  // 0x028
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_TimestampTableRow) == 44, "Size mismatch for S_TimestampTableRow");

}  // namespace wh::databasemodule
