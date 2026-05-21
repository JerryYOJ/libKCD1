#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure"  row_size: 8
// Registration: 0x180149310
#pragma pack(push, 1)
struct S_NewHomesStructureTierPrerequisity {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_id;  // 0x004  // PK
    // int32_t tier;  // 0x004 (alias)  // PK
    // int32_t required_structure_id;  // 0x004 (alias)  // PK
    // int32_t required_tier;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureTierPrerequisity) == 8, "Size mismatch for S_NewHomesStructureTierPrerequisity");

}  // namespace wh::databasemodule
