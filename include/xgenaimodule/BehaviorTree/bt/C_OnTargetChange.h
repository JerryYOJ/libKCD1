#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnTargetChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnTargetChange>  RTTI C_OnTargetChange  vtable 0x1821e4950  size 0x30  base C_CombatantHubExtended<C_PassiveBarrier>  ctx S_OnTargetChangeContext
struct S_OnTargetChangeContext;
class C_OnTargetChange : public C_NodeWrapper<C_OnTargetChange, C_CombatantHubExtended<C_PassiveBarrier>, S_OnTargetChangeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnTargetChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
