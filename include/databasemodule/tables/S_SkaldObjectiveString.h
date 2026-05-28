#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_element"  row_size: 16
// Registration: 0x18014fa20
#pragma pack(push, 1)
struct S_SkaldObjectiveString {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_element_id;  // 0x004  // PK
    // int32_t skald_objective_string_type_id;  // 0x004 (alias)  // PK
    const char* string_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldObjectiveString) == 16, "Size mismatch for S_SkaldObjectiveString");

}  // namespace wh::databasemodule
