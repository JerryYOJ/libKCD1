#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_variable_form"  row_size: 16
// Registration: 0x1801e1480
#pragma pack(push, 1)
struct S_AiVariableFormTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t ai_variable_form_id;  // 0x004  // PK
    const char* ai_variable_form_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_AiVariableFormTableRow) == 16, "Size mismatch for S_AiVariableFormTableRow");

}  // namespace wh::databasemodule
