#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_condition"  row_size: 40
// Registration: 0x1801dc780
#pragma pack(push, 1)
struct S_SoConditionTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t so_condition_id;  // 0x010  // PK
    // const char* so_condition_name;  // 0x010 (alias)
    int32_t so_condition_type_id;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* so_condition_data;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SoConditionTableRow) == 40, "Size mismatch for S_SoConditionTableRow");

}  // namespace wh::databasemodule
