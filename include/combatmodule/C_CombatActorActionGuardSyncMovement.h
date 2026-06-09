#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionGuardSyncMovementParams.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionGuardSyncMovement
    : public C_CombatActorAnimatedAction<S_CombatActorActionGuardSyncMovementParams, 1, I_CombatActorActionPrivate>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionGuardSyncMovement;
    // Primary vtable: 0x1821AB6A8 | Ctor: 0x1804315A0 | Size: 0x100
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
};
static_assert(sizeof(C_CombatActorActionGuardSyncMovement) == 0x100);

}  // namespace wh::combatmodule
