#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionBlockTriggerParams {
    uint16_t m_triggerFlags;    // +0x00  (init 1)
    uint8_t  _pad[6];           // +0x02
};
static_assert(sizeof(S_CombatActorActionBlockTriggerParams) == 0x08);

}  // namespace wh::combatmodule
