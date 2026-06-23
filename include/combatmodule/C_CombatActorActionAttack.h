#pragma once

#include <cstdint>
#include "C_CombatActorActionT.h"
#include "S_CombatActorActionAttackParams.h"
#include "I_CombatActionHelperOwner.h"
#include "C_CombatActionHelper.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActorActionAttack — normal melee attack action.
//
// RTTI: .?AVC_CombatActorActionAttack@combatmodule@wh@@
// Primary vtable:    0x1821AECA8
// Constructor: 0x180462564
// Scalar deleting dtor: 0x1804624A0
// Size: 0x138 bytes
// ---------------------------------------------------------------------------
class C_CombatActorActionAttack
    : public C_CombatActorAnimatedAction<S_CombatActorActionAttackParams, 1, I_CombatActorActionPrivate>,
      public I_CombatActionHelperAttackOwner
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionAttack;
    uint64_t                    m_unknown_110;      // +0x110  (init 0)
    bool                        m_flag_118;         // +0x118  (init 0)
    uint8_t                     _pad119[7];
    C_CombatActionHelperAttack* m_pAttackHelper;    // +0x120  alloc 0x38
    int64_t                     m_scoreSentinel;    // +0x128  int64 = -100000 (full qword store of cvttss2si(-100000.0f)); likely best/min-score init
    uint64_t                    _pad130;            // +0x130  (not ctor-initialized)
};
static_assert(sizeof(C_CombatActorActionAttack) == 0x138);

}  // namespace wh::combatmodule
