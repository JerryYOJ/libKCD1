#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionFreeBlockParams.h"

namespace wh::combatmodule {

class C_CombatActorActionFreeBlock
    : public C_CombatActorAction<I_CombatActorActionPrivate,
          C_CombatActorParamAction_Base<S_CombatActorActionFreeBlockParams, I_CombatActorActionPrivate>>
{
public:
    // Primary vtable: 0x1822C4208 | Ctor: 0x180F442F4 | Size: 0x100
    // NO C_CombatActorAnimatedAction layer
    uint16_t                    m_stateFlags;       // (init 0)
    uint8_t                     _pad1[2];
    uint32_t                    m_stateData;        // (init 0)
    _i_reference_target<int>*   m_pRefCountedObj;   // released in dtor
    float                       m_timer;            // (init -100000.0f)
    uint32_t                    _pad2;
};
static_assert(sizeof(C_CombatActorActionFreeBlock) == 0x100);

}  // namespace wh::combatmodule
