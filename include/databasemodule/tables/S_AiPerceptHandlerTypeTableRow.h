#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_percept_handler_type"  row_size: 16
// Registration: 0x1801d6110
#pragma pack(push, 1)
struct S_AiPerceptHandlerTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t ai_percept_handler_type_id;  // 0x004  // PK
    const char* ai_percept_handler_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_AiPerceptHandlerTypeTableRow) == 16, "Size mismatch for S_AiPerceptHandlerTypeTableRow");

}  // namespace wh::databasemodule
