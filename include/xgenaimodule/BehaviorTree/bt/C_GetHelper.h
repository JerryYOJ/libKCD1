#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetHelper>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetHelper>  RTTI C_GetHelper  vtable 0x18220e380  size 0x28  base C_Node  ctx S_GetHelperContext
struct S_GetHelperContext;
class C_GetHelper : public C_NodeWrapper<C_GetHelper, C_Node, S_GetHelperContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetHelper) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
