#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionSyncHitParams.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionSyncHit
    : public C_CombatActorAnimatedAction<S_CombatActorActionSyncHitParams, 1, I_CombatActorActionPrivate>
{
public:
    // Primary vtable: 0x1821BDFF0 | Ctor: 0x180565844 | Size: 0x108
    uint32_t                    m_unknown;          // (init 0)
    uint16_t                    m_flags;            // (init 0x100)
    bool                        m_flag;             // (init 0)
    uint8_t                     _pad;
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
};
static_assert(sizeof(C_CombatActorActionSyncHit) == 0x108);

}  // namespace wh::combatmodule
