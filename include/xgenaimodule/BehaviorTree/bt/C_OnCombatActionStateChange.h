#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatActionStateChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatActionStateChange>  RTTI C_OnCombatActionStateChange  vtable 0x182345a78  size 0x30  base C_CombatantHubExtended<C_PassiveBarrier>  ctx S_OnCombatActionStateChangeContext
struct S_OnCombatActionStateChangeContext;
class C_OnCombatActionStateChange : public C_NodeWrapper<C_OnCombatActionStateChange, C_CombatantHubExtended<C_PassiveBarrier>, S_OnCombatActionStateChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatActionStateChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
