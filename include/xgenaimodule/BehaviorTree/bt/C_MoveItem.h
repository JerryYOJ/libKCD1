#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MoveItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <MoveItem>  RTTI C_MoveItem  vtable 0x182333fa0  size 0x28  base C_Node  ctx S_MoveItemContext
struct S_MoveItemContext;
class C_MoveItem : public C_NodeWrapper<C_MoveItem, C_Node, S_MoveItemContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MoveItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
