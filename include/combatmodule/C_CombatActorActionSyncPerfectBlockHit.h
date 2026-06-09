#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionSyncPerfectBlockHitParams.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

class C_CombatActorActionSyncPerfectBlockHit
    : public C_CombatActorAnimatedAction<S_CombatActorActionSyncPerfectBlockHitParams, 1, I_CombatActorActionPrivate>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionSyncPerfectBlockHit;
    // Primary vtable: 0x1826A5540 | Ctor: 0x180F44688 | Size: 0x118
    // Additional MI subobject vtable at +0xF8 (from PerfectBlockHit-specific interface)
    uint64_t                    m_subobjectVtable;  // +0xF8 MI subobject vtable
    uint32_t                    m_unknown;          // (init 0)
    bool                        m_flag;             // (init 0)
    uint8_t                     _pad1[3];
    C_CombatActionSyncHelper*   m_pSyncHelper;      // alloc 0x18
    uint32_t                    m_unknown2;         // (init 0)
    uint32_t                    _pad2;
};
static_assert(sizeof(C_CombatActorActionSyncPerfectBlockHit) == 0x118);

}  // namespace wh::combatmodule
