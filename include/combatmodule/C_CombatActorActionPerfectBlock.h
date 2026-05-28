#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionPerfectBlockParams.h"

namespace wh::combatmodule {

class C_CombatActorActionPerfectBlock
    : public C_CombatActorActionPerfectBlockBase<S_CombatActorActionPerfectBlockParams, 1>
{
public:
    // Primary vtable: 0x1821B33E0 | Ctor: 0x1804E09C4 | Size: 0x150
};
static_assert(sizeof(C_CombatActorActionPerfectBlock) == 0x150);

}  // namespace wh::combatmodule
