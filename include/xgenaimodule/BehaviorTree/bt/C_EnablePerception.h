#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EnablePerception>.

namespace wh::xgenaimodule::BehaviorTree {

// <EnablePerception>  RTTI C_EnablePerception  vtable 0x18238c808  size 0x28  base C_Node  ctx S_EnablePerceptionContext
struct S_EnablePerceptionContext;
class C_EnablePerception : public C_NodeWrapper<C_EnablePerception, C_Node, S_EnablePerceptionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_EnablePerception) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
