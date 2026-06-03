#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetHelpers>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetHelpers>  RTTI C_GetHelpers  vtable 0x182322738  size 0x28  base C_Node  ctx S_GetHelpersContext
struct S_GetHelpersContext;
class C_GetHelpers : public C_NodeWrapper<C_GetHelpers, C_Node, S_GetHelpersContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetHelpers) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
