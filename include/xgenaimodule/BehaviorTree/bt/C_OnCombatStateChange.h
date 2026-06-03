#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatStateChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatStateChange>  RTTI C_OnCombatStateChange  vtable 0x1823549e0  size 0x30  base C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>  ctx S_OnCombatStateChangeContext
struct S_OnCombatStateChangeContext;
class C_OnCombatStateChange : public C_NodeWrapper<C_OnCombatStateChange, C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>, S_OnCombatStateChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatStateChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
