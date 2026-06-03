#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DistanceGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <DistanceGate>  RTTI C_DistanceGate  vtable 0x1821e3a78  size 0x30  base C_ActiveBarrier  ctx S_DistanceGateContext
struct S_DistanceGateContext;
class C_DistanceGate : public C_NodeWrapper<C_DistanceGate, C_ActiveBarrier, S_DistanceGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DistanceGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
