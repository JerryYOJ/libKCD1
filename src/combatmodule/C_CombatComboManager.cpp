#include "combatmodule/C_CombatComboManager.h"
#include "Offsets/Offsets.h"

// Direct call into the engine's combo-advance handler. a2 (the signal emitter) is unused
// by sub_180602C34; we pass m_pOwner to mirror the real signal invocation. See the header
// for the full semantics / preconditions.
void wh::combatmodule::C_CombatComboManager::ForceAdvanceStep()
{
    using Fn = void(__fastcall*)(C_CombatComboManager*, void*, char);
    static REL::Relocation<Fn> fn{ REL::ID(26) };  // sub_180602C34 combo-advance handler
    fn(this, m_pOwner, 1);
}
