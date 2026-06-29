#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/S_CombatActionAttackQueryData.h"
#include "Offsets/Offsets.h"

wh::combatmodule::I_CombatActorActionPtr* wh::combatmodule::C_CombatActionAttackFactory::CreateAndDispatch(
    I_CombatActorActionPtr* pOut, E_CombatInputClass inputClassId, int32_t flags)
{
    using Fn = I_CombatActorActionPtr*(__fastcall*)(C_CombatActionAttackFactory*, I_CombatActorActionPtr*, uint32_t, int);
    static REL::Relocation<Fn> fn{ REL::ID(21) };  // CreateAndDispatch
    return fn(this, pOut, static_cast<uint32_t>(inputClassId), flags);
}

void wh::combatmodule::C_CombatActionAttackFactory::BuildAttackQuery(
    E_CombatInputClass inputClassId, S_CombatActionAttackQueryData* q)
{
    using Fn = void(__fastcall*)(C_CombatActionAttackFactory*, uint32_t, S_CombatActionAttackQueryData*);
    static REL::Relocation<Fn> fn{ REL::ID(19) };  // BuildAttackQuery
    fn(this, static_cast<uint32_t>(inputClassId), q);
}
