#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatModeChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatModeChange>  RTTI C_OnCombatModeChange  vtable 0x182345390  size 0x30  base C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>  ctx S_OnCombatModeChangeContext
struct S_OnCombatModeChangeContext;
class C_OnCombatModeChange : public C_NodeWrapper<C_OnCombatModeChange, C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>, S_OnCombatModeChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatModeChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
