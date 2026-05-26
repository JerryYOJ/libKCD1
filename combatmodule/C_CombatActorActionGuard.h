#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionGuardParams.h"

namespace wh::combatmodule {

class C_CombatActorActionGuard
    : public C_CombatActorAction<I_CombatActorActionPrivate,
          C_CombatActorParamAction_Base<S_CombatActorActionGuardParams, I_CombatActorActionPrivate>>
{
public:
    // Primary vtable: 0x1821AEF00 (57 slots) | Ctor: 0x18046279C | Size: 0x118
    // NO C_CombatActorAnimatedAction layer
    uint16_t    m_stateFlags;       // (init 0)
    uint8_t     _pad1[2];
    uint32_t    m_unknown_EC;       // (init 0)
    uint64_t    m_unknown_F0;       // (init 0)
    uint64_t    m_unknown_F8;       // (init 0)
    uint64_t    m_unknown_100;      // (init 0)
    uint16_t    m_flags_108;        // (init 0)
    uint8_t     _pad2[2];
    uint32_t    m_unknown_10C;      // (init 0)
    uint32_t    m_unknown_110;      // (init 0)
    uint16_t    m_flags_114;        // (init 1)
    uint8_t     _pad3[2];
};
static_assert(sizeof(C_CombatActorActionGuard) == 0x118);

}  // namespace wh::combatmodule
