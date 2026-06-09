#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionSyncTransitionParams.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionSyncTransition
    : public C_CombatActorAnimatedAction<S_CombatActorActionSyncTransitionParams, 1, I_CombatActorActionPrivate>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionSyncTransition;
    // Primary vtable: 0x1822C37E0 | Ctor: 0x180F447F0 | Size: 0x110
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
    bool                        m_syncFlag;         // (init 0)
    uint8_t                     _pad[7];
};
static_assert(sizeof(C_CombatActorActionSyncTransition) == 0x110);

}  // namespace wh::combatmodule
