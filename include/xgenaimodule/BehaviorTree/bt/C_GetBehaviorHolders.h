#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetBehaviorHolders>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetBehaviorHolders>  RTTI C_GetBehaviorHolders  vtable 0x18220f338  size 0x28  base C_Node  ctx S_GetBehaviorHoldersContext
struct S_GetBehaviorHoldersContext;
class C_GetBehaviorHolders : public C_NodeWrapper<C_GetBehaviorHolders, C_Node, S_GetBehaviorHoldersContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetBehaviorHolders) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
