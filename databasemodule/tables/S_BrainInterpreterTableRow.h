#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_interpreter"  row_size: 28
// Registration: 0x1801d40e0
#pragma pack(push, 1)
struct S_BrainInterpreterTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t brain_interpreter_id;  // 0x010  // PK
    // const char* brain_interpreter_name;  // 0x010 (alias)
    int32_t brain_interpreter_type;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_BrainInterpreterTableRow) == 28, "Size mismatch for S_BrainInterpreterTableRow");

}  // namespace wh::databasemodule
