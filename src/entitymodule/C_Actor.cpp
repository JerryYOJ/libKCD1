#include "entitymodule/C_Actor.h"
#include "Offsets/Offsets.h"

wh::combatmodule::C_CombatActor* wh::entitymodule::C_Actor::GetOrCreateCombatActor()
{
    using Fn = wh::combatmodule::C_CombatActor*(__fastcall*)(C_Actor*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kGetOrCreateCombatActorOffset);
    return fn(this);
}
