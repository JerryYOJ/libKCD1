#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_input_class lookup row. ctor sub_180F995C4. VERIFIED.
struct C_CombatInputClassData {
    int32_t     combat_input_class_id;      // +0x00
    const char* combat_input_class_name;    // +0x08  CryStringT<char>
    const char* mn_tag;                     // +0x10  CryStringT<char>
};
static_assert(sizeof(C_CombatInputClassData) == 0x18);

}  // namespace wh::combatmodule
