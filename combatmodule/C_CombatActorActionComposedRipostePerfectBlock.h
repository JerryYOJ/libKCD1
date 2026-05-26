#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionComposedRipostePerfectBlockParams.h"

namespace wh::combatmodule {

class C_CombatActorActionComposedRipostePerfectBlock
    : public C_CombatActorActionPerfectBlockBase<S_CombatActorActionComposedRipostePerfectBlockParams, 2>
{
public:
    // Primary vtable: 0x1821B5E58 | Ctor: 0x1804E1C30 | Size: 0x158
};
static_assert(sizeof(C_CombatActorActionComposedRipostePerfectBlock) == 0x158);

}  // namespace wh::combatmodule
