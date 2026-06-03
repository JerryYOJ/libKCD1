#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StealthAction>.

namespace wh::xgenaimodule::BehaviorTree {

// <StealthAction>  RTTI C_StealthAction  vtable 0x182350088  size 0x28  base C_Node  ctx S_StealthActionContext
struct S_StealthActionContext;
class C_StealthAction : public C_NodeWrapper<C_StealthAction, C_Node, S_StealthActionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StealthAction) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
