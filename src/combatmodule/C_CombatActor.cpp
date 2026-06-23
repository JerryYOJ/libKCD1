#include "combatmodule/C_CombatActor.h"
#include "Offsets/Offsets.h"

void wh::combatmodule::C_CombatActor::DispatchCounterAction(
    I_CombatActorActionPtr* pOutAction, E_CounterActionType type, uint32_t scopeIndex)
{
    using Fn = void*(__fastcall*)(C_CombatActor*, I_CombatActorActionPtr*, int, uint32_t);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kDispatchCounterActionOffset);
    fn(this, pOutAction, static_cast<int>(type), scopeIndex);
}
