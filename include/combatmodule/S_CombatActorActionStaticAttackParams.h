#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

struct S_CombatActorActionStaticAttackParams : public I_CombatActorActionParamsReflect {
    ~S_CombatActorActionStaticAttackParams() = default;
    uint64_t m_data;            // +0x08  (init 0)
};
static_assert(sizeof(S_CombatActorActionStaticAttackParams) == 0x10);

}  // namespace wh::combatmodule
