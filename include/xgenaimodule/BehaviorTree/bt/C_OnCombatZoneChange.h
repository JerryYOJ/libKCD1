#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatZoneChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatZoneChange>  RTTI C_OnCombatZoneChange  vtable 0x1823546d0  size 0x30  base C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>  ctx S_OnCombatZoneChangeContext
struct S_OnCombatZoneChangeContext;
class C_OnCombatZoneChange : public C_NodeWrapper<C_OnCombatZoneChange, C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>, S_OnCombatZoneChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatZoneChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
