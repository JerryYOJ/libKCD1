#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain"  row_size: 33
// Registration: 0x1801df5c0
#pragma pack(push, 1)
struct S_SubbrainTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t subbrain_id;  // 0x010  // PK
    // const char* subbrain_name;  // 0x010 (alias)
    int32_t subbrain_type;  // 0x018
    int32_t timeout;  // 0x01C
    bool always_active;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTableRow_3) == 33, "Size mismatch for S_SubbrainTableRow_3");

}  // namespace wh::databasemodule
