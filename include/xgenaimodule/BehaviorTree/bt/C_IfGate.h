#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IfGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <IfGate>  RTTI C_IfGate  vtable 0x1821e1a18  size 0x30  base C_PassiveBarrier  ctx S_IfGateContext
struct S_IfGateContext;
class C_IfGate : public C_NodeWrapper<C_IfGate, C_PassiveBarrier, S_IfGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IfGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
