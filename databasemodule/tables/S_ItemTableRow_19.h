#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 32
// Registration: 0x1801097a0
#pragma pack(push, 1)
struct S_ItemTableRow_19 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float power;  // 0x010 (alias)
    const char* weapon_sound_switch;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_19) == 32, "Size mismatch for S_ItemTableRow_19");

}  // namespace wh::databasemodule
