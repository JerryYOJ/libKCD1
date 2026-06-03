#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetQuest>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetQuest>  RTTI C_SetQuest  vtable 0x18234b538  size 0x28  base C_Node  ctx S_SetQuestContext
struct S_SetQuestContext;
class C_SetQuest : public C_NodeWrapper<C_SetQuest, C_Node, S_SetQuestContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetQuest) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
