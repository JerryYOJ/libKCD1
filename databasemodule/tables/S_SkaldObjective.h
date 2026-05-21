#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_element"  row_size: 20
// Registration: 0x18014f4b0
#pragma pack(push, 1)
struct S_SkaldObjective {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_element_id;  // 0x004  // PK
    uint8_t _pad_0x008[4];
    int32_t objective_type_id;  // 0x00C
    int32_t is_save;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldObjective) == 20, "Size mismatch for S_SkaldObjective");

}  // namespace wh::databasemodule
