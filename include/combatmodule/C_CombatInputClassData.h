#pragma once

#include <cstdint>
#include "E_CombatInputClass.h"

namespace wh::combatmodule {

// combat_input_class lookup row. ctor sub_180F995C4. VERIFIED.
struct C_CombatInputClassData {
    E_CombatInputClass combat_input_class_id;   // +0x00  primary key = the input-class enum value (verbatim from XML)
    CryStringT<char> combat_input_class_name;   // +0x08
    CryStringT<char> mn_tag;                     // +0x10
};
static_assert(sizeof(C_CombatInputClassData) == 0x18);

}  // namespace wh::combatmodule
