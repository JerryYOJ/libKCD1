#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionSyncTransitionParams {
    uint64_t m_data;            // +0x00  (init 0)
    bool     m_flag;            // +0x08  (init 0)
    uint8_t  _pad[7];           // +0x09
};
static_assert(sizeof(S_CombatActorActionSyncTransitionParams) == 0x10);

}  // namespace wh::combatmodule
