#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "%s"  row_size: 72
// Registration: 0x1800f79e0
#pragma pack(push, 1)
struct S_GenericTableRow_2 {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t _s_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* _s_name;  // 0x020
    const char* model;  // 0x028
    const char* material;  // 0x030
    int32_t social_class_id;  // 0x038
    int32_t wealth_level;  // 0x03C
    int32_t gender_id;  // 0x040
    int32_t race_id;  // 0x044
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_GenericTableRow_2) == 72, "Size mismatch for S_GenericTableRow_2");

}  // namespace wh::databasemodule
