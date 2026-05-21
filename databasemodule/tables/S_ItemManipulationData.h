#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "id"  row_size: 32
// Registration: 0x1800fef90
#pragma pack(push, 1)
struct S_ItemManipulationData {
    uint8_t _rowbase[4];  // 0x000
    int32_t id;  // 0x004  // PK
    const char* tag;  // 0x008
    bool allow_run;  // 0x010
    bool allow_sprint;  // 0x011
    uint8_t _pad_0x012[6];
    const char* sharpening_anim;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ItemManipulationData) == 32, "Size mismatch for S_ItemManipulationData");

}  // namespace wh::databasemodule
