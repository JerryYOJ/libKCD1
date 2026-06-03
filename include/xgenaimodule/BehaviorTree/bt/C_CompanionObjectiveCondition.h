#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CompanionObjectiveCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <CompanionObjectiveCondition>  RTTI C_CompanionObjectiveCondition  vtable 0x18231c820  size 0x68  base C_Gate  ctx S_CompanionObjectiveConditionContext
struct S_CompanionObjectiveConditionContext;
class C_CompanionObjectiveCondition : public C_NodeWrapper<C_CompanionObjectiveCondition, C_Gate, S_CompanionObjectiveConditionContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_CompanionObjectiveCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
