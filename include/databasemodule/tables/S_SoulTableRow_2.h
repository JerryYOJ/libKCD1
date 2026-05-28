#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul"  row_size: 32
// Registration: 0x1801402d0
#pragma pack(push, 1)
struct S_SoulTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t soul_id;  // 0x010  // PK
    // int32_t voice_id;  // 0x010 (alias)
    const char* name_string_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_SoulTableRow_2) == 32, "Size mismatch for S_SoulTableRow_2");

}  // namespace wh::databasemodule
