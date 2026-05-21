#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x180119780
#pragma pack(push, 1)
struct S_DocumentRequirement {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // const char* script;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_DocumentRequirement) == 24, "Size mismatch for S_DocumentRequirement");

}  // namespace wh::databasemodule
