#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "parcel"  row_size: 16
// Registration: 0x1801463b0
#pragma pack(push, 1)
struct S_NewHomesParcel {
    uint8_t _rowbase[4];  // 0x000
    int32_t parcel_id;  // 0x004  // PK
    const char* parcel_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesParcel) == 16, "Size mismatch for S_NewHomesParcel");

}  // namespace wh::databasemodule
