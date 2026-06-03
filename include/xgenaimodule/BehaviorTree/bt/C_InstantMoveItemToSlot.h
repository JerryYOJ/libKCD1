#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantMoveItemToSlot>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantMoveItemToSlot>  RTTI C_InstantMoveItemToSlot  vtable 0x182334db8  size 0x28  base C_Node  ctx S_InstantMoveItemToSlotContext
struct S_InstantMoveItemToSlotContext;
class C_InstantMoveItemToSlot : public C_NodeWrapper<C_InstantMoveItemToSlot, C_Node, S_InstantMoveItemToSlotContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantMoveItemToSlot) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
