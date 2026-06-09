#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerSyncDodge ¡ª synchronized dodge.
class C_CombatTriggerSyncDodge : public C_CombatSlotTrigger {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTriggerSyncDodge;
    ~C_CombatTriggerSyncDodge() override = default;
};

}  // namespace wh::combatmodule
