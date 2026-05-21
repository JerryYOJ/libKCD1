#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_body"  row_size: 24
// Registration: 0x1801d5a90
#pragma pack(push, 1)
struct S_AiBodyTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t ai_body_id;  // 0x010  // PK
    // const char* ai_body_name;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_AiBodyTableRow_4) == 24, "Size mismatch for S_AiBodyTableRow_4");

}  // namespace wh::databasemodule
