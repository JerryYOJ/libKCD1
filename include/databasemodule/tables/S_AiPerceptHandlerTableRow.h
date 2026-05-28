#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_percept_handler"  row_size: 40
// Registration: 0x1801d5ce0
#pragma pack(push, 1)
struct S_AiPerceptHandlerTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t ai_percept_handler_id;  // 0x010  // PK
    // const char* ai_percept_handler_name;  // 0x010 (alias)
    int32_t ai_percept_handler_type;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* data;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_AiPerceptHandlerTableRow) == 40, "Size mismatch for S_AiPerceptHandlerTableRow");

}  // namespace wh::databasemodule
