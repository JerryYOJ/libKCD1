#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain"  row_size: 24
// Registration: 0x1801dfe30
#pragma pack(push, 1)
struct S_SubbrainTableRow_5 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t subbrain_id;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTableRow_5) == 24, "Size mismatch for S_SubbrainTableRow_5");

}  // namespace wh::databasemodule
