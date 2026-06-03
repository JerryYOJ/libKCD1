#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DistanceCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <DistanceCondition>  RTTI C_DistanceCondition  vtable 0x1822078b8  size 0x48  base C_Decorator  ctx S_DistanceConditionContext
struct S_DistanceConditionContext;
class C_DistanceCondition : public C_NodeWrapper<C_DistanceCondition, C_Decorator, S_DistanceConditionContext>
{
    uint8_t _ownState[0x18];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_DistanceCondition) == 0x48);

}  // namespace wh::xgenaimodule::BehaviorTree
