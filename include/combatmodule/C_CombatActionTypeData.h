#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_action_type lookup row. ctor sub_180F927D8. VERIFIED.
// Value of C_AnimationDatabaseStaticIndexed<C_CombatActionTypeData, S_CombatActionTypeTableRow>.
struct C_CombatActionTypeData {
    int32_t     combat_action_type_id;      // +0x00
    const char* combat_action_type_name;    // +0x08  CryStringT<char>
};
static_assert(sizeof(C_CombatActionTypeData) == 0x10);

}  // namespace wh::combatmodule
