#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "iso"  row_size: 24
// Registration: 0x18012af60
#pragma pack(push, 1)
struct S_RichPresenceTextDBData {
    uint8_t _rowbase[8];  // 0x000
    const char* iso_code;  // 0x008
    const char* text;  // 0x010
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* string_name;
};
#pragma pack(pop)
static_assert(sizeof(S_RichPresenceTextDBData) == 24, "Size mismatch for S_RichPresenceTextDBData");

}  // namespace wh::databasemodule
