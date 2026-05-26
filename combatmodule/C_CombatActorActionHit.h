#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionHitParams.h"

namespace wh::combatmodule {

class C_CombatActorActionHit
    : public C_CombatActorAnimatedAction<S_CombatActorActionHitParams, 2, I_CombatActorActionPrivate>
{
public:
    // Primary vtable: 0x1821B44C0 | Ctor: 0x1804E1020 | Size: 0x118
    // N=2: 2 animation scopes
    uint32_t    m_unknown_110;      // (init 0)
    uint32_t    m_unknown_114;      // (init 0)
};
static_assert(sizeof(C_CombatActorActionHit) == 0x118);

}  // namespace wh::combatmodule
