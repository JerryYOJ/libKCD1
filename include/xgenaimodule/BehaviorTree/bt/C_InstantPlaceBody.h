#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantPlaceBody>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantPlaceBody>  RTTI C_InstantPlaceBody  vtable 0x18232b068  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_InstantPlaceBody : public C_NodeWrapper<C_InstantPlaceBody, C_Node, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantPlaceBody) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
