#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionGuardMovementParams.h"

namespace wh::combatmodule {

class C_CombatActorActionRiderMovement
    : public C_CombatActorAnimatedAction<S_CombatActorActionGuardMovementParams, 1, I_CombatActorActionPrivate>
{
public:
    // Primary vtable: 0x1822C4030 | Ctor: 0x180F44354 | Size: 0x100
    // Shares S_CombatActorActionGuardMovementParams with GuardMovement
    bool        m_isRider;          // (init 1 — only field beyond GuardMovement)
    uint8_t     _pad[7];
};
static_assert(sizeof(C_CombatActorActionRiderMovement) == 0x100);

}  // namespace wh::combatmodule
