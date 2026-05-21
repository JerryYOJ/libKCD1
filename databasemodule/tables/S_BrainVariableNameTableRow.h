#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_variable_name"  row_size: 48
// Registration: 0x1801d3790
#pragma pack(push, 1)
struct S_BrainVariableNameTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* brain_variable_name;  // 0x008  // PK
    uint64_t brain_id;  // 0x010  // PK
    const char* type;  // 0x018
    int32_t ai_variable_form_id;  // 0x020
    int32_t ai_variable_sync_id;  // 0x024
    const char* init_value;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_BrainVariableNameTableRow) == 48, "Size mismatch for S_BrainVariableNameTableRow");

}  // namespace wh::databasemodule
