#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "angriness_enum"  row_size: 8
// Registration: 0x180116e20
#pragma pack(push, 1)
struct S_AngrinessEnum {
    uint8_t _rowbase[4];  // 0x000
    int32_t angriness_enum_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_AngrinessEnum) == 8, "Size mismatch for S_AngrinessEnum");

}  // namespace wh::databasemodule
