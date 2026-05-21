#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "role"  row_size: 20
// Registration: 0x180120830
#pragma pack(push, 1)
struct S_Role {
    uint8_t _rowbase[4];  // 0x000
    int32_t role_id;  // 0x004  // PK
    const char* role_name;  // 0x008
    int32_t metarole_id;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_Role) == 20, "Size mismatch for S_Role");

}  // namespace wh::databasemodule
