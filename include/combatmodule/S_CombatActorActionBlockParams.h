#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

struct S_CombatActorActionBlockParams : public I_CombatActorActionParamsReflect {
    inline static constexpr auto RTTI = Offsets::RTTI_S_CombatActorActionBlockParams;
    ~S_CombatActorActionBlockParams() = default;
    uint64_t m_data;            // +0x08  (init 0)
};
static_assert(sizeof(S_CombatActorActionBlockParams) == 0x10);

}  // namespace wh::combatmodule
