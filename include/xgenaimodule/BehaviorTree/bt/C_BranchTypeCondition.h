#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BranchTypeCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <BranchTypeCondition>  RTTI C_BranchTypeCondition  vtable 0x182356dc8  size 0x68  base C_Gate  ctx S_BranchTypeConditionContext
struct S_BranchTypeConditionContext;
class C_BranchTypeCondition : public C_NodeWrapper<C_BranchTypeCondition, C_Gate, S_BranchTypeConditionContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_BranchTypeCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
