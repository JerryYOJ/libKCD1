#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetEstimatedFollow>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetEstimatedFollow>  RTTI C_SetEstimatedFollow  vtable 0x18236e468  size 0x28  base C_Node  ctx S_SetEstimatedFollowContext
struct S_SetEstimatedFollowContext;
class C_SetEstimatedFollow : public C_NodeWrapper<C_SetEstimatedFollow, C_Node, S_SetEstimatedFollowContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetEstimatedFollow) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
