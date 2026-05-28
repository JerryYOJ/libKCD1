#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_role"  row_size: 48
// Registration: 0x1801da4c0
#pragma pack(push, 1)
struct S_SituationRoleTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_role_id;  // 0x010  // PK
    // uint64_t situation_variant_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    const char* tree_file;  // 0x020
    const char* tree_name;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_SituationRoleTableRow_2) == 48, "Size mismatch for S_SituationRoleTableRow_2");

}  // namespace wh::databasemodule
