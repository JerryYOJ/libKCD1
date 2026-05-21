#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_body"  row_size: 24
// Registration: 0x1801d5840
#pragma pack(push, 1)
struct S_AiBodyTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t ai_body_id;  // 0x010  // PK
    // uint64_t brain_sensor_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_AiBodyTableRow_3) == 24, "Size mismatch for S_AiBodyTableRow_3");

}  // namespace wh::databasemodule
