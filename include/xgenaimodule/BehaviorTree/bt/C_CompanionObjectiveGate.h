#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CompanionObjectiveGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <CompanionObjectiveGate>  RTTI C_CompanionObjectiveGate  vtable 0x18221bb18  size 0x30  base C_NPCPassiveBarrier  ctx S_CompanionObjectiveGateContext
struct S_CompanionObjectiveGateContext;
class C_CompanionObjectiveGate : public C_NodeWrapper<C_CompanionObjectiveGate, C_NPCPassiveBarrier, S_CompanionObjectiveGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_CompanionObjectiveGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
