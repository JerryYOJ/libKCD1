#include "entitymodule/C_Actor.h"
#include "Offsets/Offsets.h"

wh::combatmodule::C_CombatActor* wh::entitymodule::C_Actor::GetOrCreateCombatActor()
{
    using Fn = wh::combatmodule::C_CombatActor*(__fastcall*)(C_Actor*);
    static REL::Relocation<Fn> fn{ REL::ID(13) };  // C_Actor::GetOrCreateCombatActor
    return fn(this);
}
