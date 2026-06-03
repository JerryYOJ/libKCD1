#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <QuestCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <QuestCondition>  RTTI C_QuestCondition  vtable 0x182365010  size 0x68  base C_Gate  ctx S_QuestConditionContext
struct S_QuestConditionContext;
class C_QuestCondition : public C_NodeWrapper<C_QuestCondition, C_Gate, S_QuestConditionContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_QuestCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
