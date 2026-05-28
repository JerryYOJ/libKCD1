#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerSyncRiposte ¡ª synchronized riposte.
class C_CombatTriggerSyncRiposte : public C_CombatSlotTrigger {
public:
    ~C_CombatTriggerSyncRiposte() override = default;
};

}  // namespace wh::combatmodule
