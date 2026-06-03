#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LogToTimedLabel>.

namespace wh::xgenaimodule::BehaviorTree {

// <LogToTimedLabel>  RTTI C_LogToTimedLabel  vtable 0x182332c20  size 0x28  base C_Node  ctx S_LogToTimedLabelContext
struct S_LogToTimedLabelContext;
class C_LogToTimedLabel : public C_NodeWrapper<C_LogToTimedLabel, C_Node, S_LogToTimedLabelContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_LogToTimedLabel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
