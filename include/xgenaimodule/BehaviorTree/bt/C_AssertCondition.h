#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AssertCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <AssertCondition>  RTTI C_AssertCondition  vtable 0x18231dbb0  size 0x28  base C_Node  ctx S_AssertConditionContext
struct S_AssertConditionContext;
class C_AssertCondition : public C_NodeWrapper<C_AssertCondition, C_Node, S_AssertConditionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AssertCondition) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
