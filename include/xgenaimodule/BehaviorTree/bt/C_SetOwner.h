#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetOwner>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetOwner>  RTTI C_SetOwner  vtable 0x18233b210  size 0x28  base C_Node  ctx S_SetOwnerContext
struct S_SetOwnerContext;
class C_SetOwner : public C_NodeWrapper<C_SetOwner, C_Node, S_SetOwnerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetOwner) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
