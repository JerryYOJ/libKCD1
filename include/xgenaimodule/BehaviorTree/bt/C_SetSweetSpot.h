#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetSweetSpot>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetSweetSpot>  RTTI C_SetSweetSpot  vtable 0x182349ae0  size 0x28  base C_Node  ctx S_SetSweetSpotContext
struct S_SetSweetSpotContext;
class C_SetSweetSpot : public C_NodeWrapper<C_SetSweetSpot, C_Node, S_SetSweetSpotContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetSweetSpot) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
