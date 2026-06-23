#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/S_CombatActionAttackQueryData.h"
#include "Offsets/Offsets.h"

wh::combatmodule::I_CombatActorActionPtr* wh::combatmodule::C_CombatActionAttackFactory::CreateAndDispatch(
    I_CombatActorActionPtr* pOut, E_CombatInputClass inputClassId, int32_t flags)
{
    using Fn = I_CombatActorActionPtr*(__fastcall*)(C_CombatActionAttackFactory*, I_CombatActorActionPtr*, uint32_t, int);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kCreateAndDispatchOffset);
    return fn(this, pOut, static_cast<uint32_t>(inputClassId), flags);
}

void wh::combatmodule::C_CombatActionAttackFactory::BuildAttackQuery(
    E_CombatInputClass inputClassId, S_CombatActionAttackQueryData* q)
{
    using Fn = void(__fastcall*)(C_CombatActionAttackFactory*, uint32_t, S_CombatActionAttackQueryData*);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kBuildAttackQueryOffset);
    fn(this, static_cast<uint32_t>(inputClassId), q);
}
