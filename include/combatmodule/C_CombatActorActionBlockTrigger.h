#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionBlockTriggerParams.h"

namespace wh::combatmodule {

class C_CombatActorActionBlockTrigger
    : public C_CombatActorAction<I_CombatActorActionPrivate,
          C_CombatActorParamAction_Base<S_CombatActorActionBlockTriggerParams, I_CombatActorActionPrivate>>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionBlockTrigger;
    // Primary vtable: 0x1821DB520 | Ctor: 0x180688FA0 | Size: 0xF8
    // NO C_CombatActorAnimatedAction layer
    uint16_t    m_stateFlags;       // (init 0)
    uint8_t     _pad1[2];
    uint32_t    m_unknown;          // (init 0)
    bool        m_flag;             // (init 0)
    uint8_t     _pad2[7];
};
static_assert(sizeof(C_CombatActorActionBlockTrigger) == 0xF8);

}  // namespace wh::combatmodule
