#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_variable_sync"  row_size: 16
// Registration: 0x1801e16d0
#pragma pack(push, 1)
struct S_AiVariableSyncTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t ai_variable_sync_id;  // 0x004  // PK
    const char* ai_variable_sync_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_AiVariableSyncTableRow) == 16, "Size mismatch for S_AiVariableSyncTableRow");

}  // namespace wh::databasemodule
