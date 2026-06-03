#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EnableLink>.

namespace wh::xgenaimodule::BehaviorTree {

// <EnableLink>  RTTI C_EnableLink  vtable 0x182373af0  size 0x28  base C_Node  ctx S_EnableLinkContext
struct S_EnableLinkContext;
class C_EnableLink : public C_NodeWrapper<C_EnableLink, C_Node, S_EnableLinkContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_EnableLink) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
