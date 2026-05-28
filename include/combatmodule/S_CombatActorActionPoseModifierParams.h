#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionPoseModifierParams {
    uint64_t m_data;            // +0x00  (init 0)
};
static_assert(sizeof(S_CombatActorActionPoseModifierParams) == 0x08);

}  // namespace wh::combatmodule
