#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_element"  row_size: 24
// Registration: 0x1800e7f70
#pragma pack(push, 1)
struct S_SkaldElementTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_element_id;  // 0x004  // PK
    // int32_t skald_subchapter_id;  // 0x004 (alias)
    int32_t skald_element_type;  // 0x008
    uint8_t _pad_0x00C[4];
    const char* skald_name;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldElementTableRow_2) == 24, "Size mismatch for S_SkaldElementTableRow_2");

}  // namespace wh::databasemodule
