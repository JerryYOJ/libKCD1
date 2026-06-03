#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StateMachineGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <StateMachineGate>  RTTI C_StateMachineGate  vtable 0x182377348  size 0x30  base C_PassiveBarrier  ctx S_StateMachineGateContext
struct S_StateMachineGateContext;
class C_StateMachineGate : public C_NodeWrapper<C_StateMachineGate, C_PassiveBarrier, S_StateMachineGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_StateMachineGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
