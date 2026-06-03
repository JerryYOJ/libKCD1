#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Boid>.

namespace wh::xgenaimodule::BehaviorTree {

// <Boid>  RTTI C_Boid  vtable 0x18231dc78  size 0x28  base C_Node  ctx S_BoidContext
struct S_BoidContext;
class C_Boid : public C_NodeWrapper<C_Boid, C_Node, S_BoidContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Boid) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
