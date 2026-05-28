#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure"  row_size: 8
// Registration: 0x180149710
#pragma pack(push, 1)
struct S_NewHomesStructureTierResourcePrerequisity {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_id;  // 0x004  // PK
    // int32_t tier;  // 0x004 (alias)  // PK
    // int32_t resource_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureTierResourcePrerequisity) == 8, "Size mismatch for S_NewHomesStructureTierResourcePrerequisity");

}  // namespace wh::databasemodule
