#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_side lookup row. ctor sub_180F99784; field order matches the RE'd
// S_CombatSideDBData table row. VERIFIED.
struct C_CombatSideData {
    int32_t     combat_side_id;             // +0x00
    const char* combat_side_name;           // +0x08  CryStringT<char>
    const char* mn_tag;                     // +0x10  CryStringT<char>
    float       angle_from;                 // +0x18
    float       angle_to;                   // +0x1C
    int32_t     combat_action_type_id;      // +0x20
    int32_t     _runtime24;                 // +0x24  zero-init runtime
    int32_t     _runtime28;                 // +0x28
    int32_t     _runtime2C;                 // +0x2C
};
static_assert(sizeof(C_CombatSideData) == 0x30);

}  // namespace wh::combatmodule
