#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_guard_stance lookup row. OnPostLoad ctor sub_180F9DA5C (mn-tag-backed:
// strings followed by a runtime block). Field order matches S_CombatGuardStanceTableRow.
// VERIFIED.
struct C_CombatGuardStanceData {
    int32_t     combat_guard_stance_id;     // +0x00
    const char* combat_guard_stance_name;   // +0x08  CryStringT<char>
    const char* mn_tag;                     // +0x10  CryStringT<char>
    const char* opp_mn_tag;                 // +0x18  CryStringT<char>
    uint8_t     _runtime20[0x18];           // +0x20  zero-init runtime (mn fragment data)
};
static_assert(sizeof(C_CombatGuardStanceData) == 0x38);

}  // namespace wh::combatmodule
