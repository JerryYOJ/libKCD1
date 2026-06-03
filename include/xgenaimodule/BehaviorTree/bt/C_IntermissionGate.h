#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IntermissionGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <IntermissionGate>  RTTI C_IntermissionGate  vtable 0x18236bbd8  size 0x30  base C_PassiveBarrier  ctx S_IntermissionGateContext
struct S_IntermissionGateContext;
class C_IntermissionGate : public C_NodeWrapper<C_IntermissionGate, C_PassiveBarrier, S_IntermissionGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IntermissionGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
