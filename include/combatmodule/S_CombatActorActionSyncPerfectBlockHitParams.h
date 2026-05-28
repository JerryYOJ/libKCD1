#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionSyncPerfectBlockHitParams {
    uint64_t m_data;            // +0x00  (init 0)
};
static_assert(sizeof(S_CombatActorActionSyncPerfectBlockHitParams) == 0x08);

}  // namespace wh::combatmodule
