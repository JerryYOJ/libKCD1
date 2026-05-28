#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "text_type"  row_size: 24
// Registration: 0x18012bc40
#pragma pack(push, 1)
struct S_SPHighlightTextData {
    uint8_t _rowbase[4];  // 0x000
    int32_t text_type;  // 0x004  // PK
    // int32_t achievement_id;  // 0x004 (alias)  // PK
    const char* text;  // 0x008
    const char* ietf_language_tag;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_SPHighlightTextData) == 24, "Size mismatch for S_SPHighlightTextData");

}  // namespace wh::databasemodule
