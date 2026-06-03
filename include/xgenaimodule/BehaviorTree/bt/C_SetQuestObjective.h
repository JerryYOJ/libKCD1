#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetQuestObjective>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetQuestObjective>  RTTI C_SetQuestObjective  vtable 0x182220170  size 0x28  base C_Node  ctx S_SetQuestObjectiveContext
struct S_SetQuestObjectiveContext;
class C_SetQuestObjective : public C_NodeWrapper<C_SetQuestObjective, C_Node, S_SetQuestObjectiveContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetQuestObjective) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
