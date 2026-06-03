#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DeadUnconsciousGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <DeadUnconsciousGate>  RTTI C_DeadUnconsciousGate  vtable 0x182214838  size 0x30  base C_PassiveBarrier  ctx S_DeadUnconsciousGateContext
struct S_DeadUnconsciousGateContext;
class C_DeadUnconsciousGate : public C_NodeWrapper<C_DeadUnconsciousGate, C_PassiveBarrier, S_DeadUnconsciousGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DeadUnconsciousGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
