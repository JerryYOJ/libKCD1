#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_weapon_group lookup row. ctor sub_180F9984C. VERIFIED.
struct C_CombatWeaponGroupData {
    int32_t     combat_weapon_group_id;     // +0x00
    const char* combat_weapon_group_name;   // +0x08  CryStringT<char>
    const char* mn_tag;                     // +0x10  CryStringT<char>
    int32_t     combat_priority;            // +0x18
    int32_t     _pad1C;                     // +0x1C
};
static_assert(sizeof(C_CombatWeaponGroupData) == 0x20);

}  // namespace wh::combatmodule
