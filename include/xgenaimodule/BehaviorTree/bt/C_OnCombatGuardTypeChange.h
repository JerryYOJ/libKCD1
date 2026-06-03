#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatGuardTypeChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatGuardTypeChange>  RTTI C_OnCombatGuardTypeChange  vtable 0x182345720  size 0x30  base C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>  ctx S_OnCombatGuardTypeChangeContext
struct S_OnCombatGuardTypeChangeContext;
class C_OnCombatGuardTypeChange : public C_NodeWrapper<C_OnCombatGuardTypeChange, C_CombatantHubExtended<C_ForwardingData<C_PassiveBarrier>>, S_OnCombatGuardTypeChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatGuardTypeChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
