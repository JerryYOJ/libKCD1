#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 57
// Registration: 0x180107880
#pragma pack(push, 1)
struct S_ItemTableRow_13 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // const char* latin_name;  // 0x010 (alias)
    const char* ui_desc;  // 0x018
    const char* ui_effect;  // 0x020
    const char* ui_occur;  // 0x028
    int32_t element1_id;  // 0x030
    int32_t element2_id;  // 0x034
    bool poisonous;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_13) == 57, "Size mismatch for S_ItemTableRow_13");

}  // namespace wh::databasemodule
