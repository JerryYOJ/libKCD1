#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_message_type"  row_size: 16
// Registration: 0x1801d53a0
#pragma pack(push, 1)
struct S_BrainMessageTypeTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t brain_message_type_id;  // 0x004  // PK
    const char* brain_message_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_BrainMessageTypeTableRow_2) == 16, "Size mismatch for S_BrainMessageTypeTableRow_2");

}  // namespace wh::databasemodule
