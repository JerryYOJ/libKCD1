#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddLink>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddLink>  RTTI C_AddLink  vtable 0x1821f9bf8  size 0x28  base C_Node  ctx S_AddLinkContext
struct S_AddLinkContext;
class C_AddLink : public C_NodeWrapper<C_AddLink, C_Node, S_AddLinkContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddLink) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
