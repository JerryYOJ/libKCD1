#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionPerfectBlockParams.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionSyncPerfectBlock
    : public C_CombatActorActionPerfectBlockBase<S_CombatActorActionPerfectBlockParams, 1>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionSyncPerfectBlock;
    // Primary vtable: 0x1822C3B18 (61 slots) | Ctor: 0x180F44528 | Size: 0x160
    // LARGEST action class
    bool                        m_syncFlag;         // (init 0)
    uint8_t                     _pad[7];
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
};
static_assert(sizeof(C_CombatActorActionSyncPerfectBlock) == 0x160);

}  // namespace wh::combatmodule
