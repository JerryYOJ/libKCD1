#pragma once

#include "I_CombatActorAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActorActionBlock — extended interface for block actions.
//
// RTTI: .?AVI_CombatActorActionBlock@combatmodule@wh@@
// Extends I_CombatActorActionPrivate with block-specific methods.
// Only used by C_CombatActorActionBlock (not PerfectBlock or FreeBlock).
// ---------------------------------------------------------------------------
class I_CombatActorActionBlock : public I_CombatActorActionPrivate {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatActorActionBlock;
    // No additional methods identified beyond I_CombatActorActionPrivate.
    // Block uses this as its primary interface type parameter in the
    // template chain: C_Action<I_CombatActorActionBlock>.
};

}  // namespace wh::combatmodule
