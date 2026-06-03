#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetOwner>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetOwner>  RTTI C_GetOwner  vtable 0x18232cab8  size 0x28  base C_Node  ctx S_GetOwnerContext
struct S_GetOwnerContext;
class C_GetOwner : public C_NodeWrapper<C_GetOwner, C_Node, S_GetOwnerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetOwner) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
