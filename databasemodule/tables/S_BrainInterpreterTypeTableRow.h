#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_interpreter_type"  row_size: 16
// Registration: 0x1801d4420
#pragma pack(push, 1)
struct S_BrainInterpreterTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t brain_interpreter_type_id;  // 0x004  // PK
    const char* brain_interpreter_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_BrainInterpreterTypeTableRow) == 16, "Size mismatch for S_BrainInterpreterTypeTableRow");

}  // namespace wh::databasemodule
