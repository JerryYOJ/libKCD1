#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_message_type"  row_size: 24
// Registration: 0x1801dec00
#pragma pack(push, 1)
struct S_BrainMessageTypeTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t brain_message_type_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t subbrain_id;  // 0x010  // PK
    // uint64_t ai_percept_handler_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_BrainMessageTypeTableRow_3) == 24, "Size mismatch for S_BrainMessageTypeTableRow_3");

}  // namespace wh::databasemodule
