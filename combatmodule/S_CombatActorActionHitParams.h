#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct S_CombatActorActionHitParams {
    uint64_t m_data1;           // +0x00  (init 0)
    uint64_t m_data2;           // +0x08  (init 0)
    uint8_t  m_flags;           // +0x10  (init: low 2 bits cleared)
    uint8_t  _pad[7];           // +0x11
};
static_assert(sizeof(S_CombatActorActionHitParams) == 0x18);

}  // namespace wh::combatmodule
