#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "judgement"  row_size: 24
// Registration: 0x1801443e0
#pragma pack(push, 1)
struct S_NewHomesJudgement {
    uint8_t _rowbase[4];  // 0x000
    int32_t judgement_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    const char* layer_profile;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesJudgement) == 24, "Size mismatch for S_NewHomesJudgement");

}  // namespace wh::databasemodule
