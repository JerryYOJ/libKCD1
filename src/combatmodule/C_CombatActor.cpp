#include "combatmodule/C_CombatActor.h"
#include "Offsets/Offsets.h"

void wh::combatmodule::C_CombatActor::DispatchCounterAction(
    I_CombatActorActionPtr* pOutAction, E_CounterActionType type, uint32_t scopeIndex)
{
    using Fn = void*(__fastcall*)(C_CombatActor*, I_CombatActorActionPtr*, int, uint32_t);
    static REL::Relocation<Fn> fn{ REL::ID(31) };
    fn(this, pOutAction, static_cast<int>(type), scopeIndex);
}

// sub_18063A634 — engage `target` as this actor's 1v1 opponent (drives the opponent
// manager's UpdateOpponent; no-op unless m_isActive).
void wh::combatmodule::C_CombatActor::SetOpponent(C_CombatActor* target)
{
    using Fn = void(__fastcall*)(C_CombatActor*, C_CombatActor*);
    static REL::Relocation<Fn> fn{ REL::ID(27) };
    fn(this, target);
}
