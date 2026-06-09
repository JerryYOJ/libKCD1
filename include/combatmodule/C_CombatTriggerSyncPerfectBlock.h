#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerSyncPerfectBlock ¡ª synchronized PB (2-actor).
class C_CombatTriggerSyncPerfectBlock : public C_CombatSlotTrigger {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTriggerSyncPerfectBlock;
    ~C_CombatTriggerSyncPerfectBlock() override = default;
};

}  // namespace wh::combatmodule
