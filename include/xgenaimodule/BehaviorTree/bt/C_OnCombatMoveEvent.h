#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "C_CombatantHubExtended.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatMoveEvent>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatMoveEvent>  RTTI C_OnCombatMoveEvent  vtable 0x1821f3a80  size 0x30  base C_CombatantHubExtended<C_DeferredExecution>  ctx S_OnCombatMoveEventContext
struct S_OnCombatMoveEventContext;
class C_OnCombatMoveEvent : public C_NodeWrapper<C_OnCombatMoveEvent, C_CombatantHubExtended<C_DeferredExecution>, S_OnCombatMoveEventContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatMoveEvent) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
