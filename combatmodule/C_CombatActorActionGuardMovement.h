#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionGuardMovementParams.h"

namespace wh::combatmodule {

class C_CombatActorActionGuardMovement
    : public C_CombatActorAnimatedAction<S_CombatActorActionGuardMovementParams, 1, I_CombatActorActionPrivate>
{
public:
    // Primary vtable: 0x1821AB900 | Ctor: 0x180433630 | Size: 0xF8
    // Smallest animated action — no leaf data beyond base
};
static_assert(sizeof(C_CombatActorActionGuardMovement) == 0xF8);

}  // namespace wh::combatmodule
