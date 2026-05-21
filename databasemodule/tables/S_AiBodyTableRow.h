#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_body"  row_size: 16
// Registration: 0x1801d26e0
#pragma pack(push, 1)
struct S_AiBodyTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t ai_body_id;  // 0x004  // PK
    const char* smart_object_template_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_AiBodyTableRow) == 16, "Size mismatch for S_AiBodyTableRow");

}  // namespace wh::databasemodule
