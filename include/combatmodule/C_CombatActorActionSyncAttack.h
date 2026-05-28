#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionSyncAttackParams.h"
#include "I_CombatActionHelperOwner.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionSyncAttack
    : public C_CombatActorAnimatedAction<S_CombatActorActionSyncAttackParams, 1, I_CombatActorActionPrivate>,
      public I_CombatActionHelperAttackOwner
{
public:
    // Primary vtable: 0x1821AD970 | Ctor: 0x180461E10 | Size: 0x128
    C_CombatActionHelperAttack* m_pAttackHelper;    // alloc 0x38
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
    bool                        m_syncFlag;         // (init 0)
    uint8_t                     _pad[7];
};
static_assert(sizeof(C_CombatActorActionSyncAttack) == 0x128);

}  // namespace wh::combatmodule
