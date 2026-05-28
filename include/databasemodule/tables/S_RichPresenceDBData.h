#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "rich_presence"  row_size: 24
// Registration: 0x18012ac40
#pragma pack(push, 1)
struct S_RichPresenceDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t rich_presence_id;  // 0x004  // PK
    const char* name_string_id;  // 0x008
    const char* xbox_rich_presence_key;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_RichPresenceDBData) == 24, "Size mismatch for S_RichPresenceDBData");

}  // namespace wh::databasemodule
