#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain"  row_size: 24
// Registration: 0x1801d3540
#pragma pack(push, 1)
struct S_BrainTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t brain_id;  // 0x010  // PK
    // const char* brain_name;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_BrainTableRow_4) == 24, "Size mismatch for S_BrainTableRow_4");

}  // namespace wh::databasemodule
