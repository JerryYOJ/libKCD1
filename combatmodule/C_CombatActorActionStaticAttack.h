#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionStaticAttackParams.h"
#include "I_CombatActionHelperOwner.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionStaticAttack
    : public C_CombatActorAnimatedAction<S_CombatActorActionStaticAttackParams, 1, I_CombatActorActionPrivate>,
      public I_CombatActionHelperAttackOwner
{
public:
    // Primary vtable: 0x1822C3D90 | Ctor: 0x180F443AC | Size: 0x110
    C_CombatActionHelperAttack* m_pAttackHelper;    // alloc 0x38
};
static_assert(sizeof(C_CombatActorActionStaticAttack) == 0x110);

}  // namespace wh::combatmodule
