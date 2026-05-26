#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionGuardParams {
    uint64_t m_data;            // +0x00
};
static_assert(sizeof(S_CombatActorActionGuardParams) == 0x08);

}  // namespace wh::combatmodule
