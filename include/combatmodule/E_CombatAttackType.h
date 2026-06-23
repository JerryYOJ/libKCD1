#pragma once

#include <cstdint>

namespace wh::combatmodule {

// combat_attack_type id (Tables.pak). FK target of C_CombatComboStepData.m_attackTypeId
// and the per-attack physical type. VERIFIED from combat_attack_type.xml.
enum class E_CombatAttackType : int32_t {
    None    = -1,   // "none" — a directional combo step carries this
    Stab    = 0,
    Slash   = 1,
    Smash   = 2,
    Throw   = 3,    // cannot_kill
    Kick    = 4,    // cannot_kill
    Punch   = 5,    // cannot_kill
    Hook    = 6,    // cannot_kill
    Direct  = 7,    // cannot_kill
    Bite    = 8,
    Backoff = 9,    // cannot_kill
};

}  // namespace wh::combatmodule
