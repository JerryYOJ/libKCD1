#include "combatmodule/S_CombatActorState.h"
#include "combatmodule/E_CombatInputClass.h"
#include "combatmodule/E_CombatZoneId.h"
#include "Offsets/Offsets.h"

void wh::combatmodule::S_CombatActorState::SetCommittedAttackZone(E_CombatZoneId zone)
{
    using Fn = void(__fastcall*)(S_CombatActorState*, int);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kSetCommittedAttackZoneOffset);
    fn(this, static_cast<int>(zone));
}
