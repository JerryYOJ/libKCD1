#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantPickUpBody>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantPickUpBody>  RTTI C_InstantPickUpBody  vtable 0x18232b2e8  size 0x28  base C_Node  ctx S_InstantPickUpBodyContext
struct S_InstantPickUpBodyContext;
class C_InstantPickUpBody : public C_NodeWrapper<C_InstantPickUpBody, C_Node, S_InstantPickUpBodyContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantPickUpBody) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
