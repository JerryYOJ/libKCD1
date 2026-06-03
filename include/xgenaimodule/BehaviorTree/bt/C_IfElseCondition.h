#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IfElseCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <IfElseCondition>  RTTI C_IfElseCondition  vtable 0x18219fbb8  size 0x68  base C_Gate  ctx S_IfElseConditionContext
struct S_IfElseConditionContext;
class C_IfElseCondition : public C_NodeWrapper<C_IfElseCondition, C_Gate, S_IfElseConditionContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IfElseCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
