#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerSyncRiposte ¡ª synchronized riposte.
class C_CombatTriggerSyncRiposte : public C_CombatSlotTrigger {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTriggerSyncRiposte;
    ~C_CombatTriggerSyncRiposte() override = default;
};

}  // namespace wh::combatmodule
