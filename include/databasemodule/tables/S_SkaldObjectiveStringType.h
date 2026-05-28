#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_objective_string_type"  row_size: 16
// Registration: 0x18014fd40
#pragma pack(push, 1)
struct S_SkaldObjectiveStringType {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_objective_string_type_id;  // 0x004  // PK
    const char* skald_objective_string_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldObjectiveStringType) == 16, "Size mismatch for S_SkaldObjectiveStringType");

}  // namespace wh::databasemodule
