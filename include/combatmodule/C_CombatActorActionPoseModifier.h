#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionPoseModifierParams.h"

namespace wh::combatmodule {

class C_CombatActorActionPoseModifier
    : public C_CombatActorAnimatedAction<S_CombatActorActionPoseModifierParams, 1, I_CombatActorActionPrivate>
{
public:
    // Primary vtable: 0x1821AC250 | Ctor: 0x180433EEC | Size: 0x108
    // Action state initialized to 4 (priority = 4)
    bool        m_flag;             // (init 0)
    uint8_t     _pad[7];
    float       m_timer;            // (init -100000.0f)
    uint32_t    _pad2;
};
static_assert(sizeof(C_CombatActorActionPoseModifier) == 0x108);

}  // namespace wh::combatmodule
