#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skill"  row_size: 85
// Registration: 0x180122ae0
#pragma pack(push, 1)
struct S_Skill {
    uint8_t _rowbase[4];  // 0x000
    int32_t skill_id;  // 0x004  // PK
    const char* skill_name;  // 0x008
    int32_t icon_id;  // 0x010
    uint8_t _pad_0x014[4];
    const char* skill_desc_nolevel;  // 0x018
    const char* skill_desc_beginner;  // 0x020
    const char* skill_desc_adept;  // 0x028
    const char* skill_desc_expert;  // 0x030
    const char* skill_desc_master;  // 0x038
    const char* ui_string_name;  // 0x040
    const char* ui_levelup_string_name;  // 0x048
    uint8_t _pad_0x050[4];
    bool hidden;  // 0x054
};
#pragma pack(pop)
static_assert(sizeof(S_Skill) == 85, "Size mismatch for S_Skill");

}  // namespace wh::databasemodule
