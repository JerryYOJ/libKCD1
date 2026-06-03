#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisablePerception>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisablePerception>  RTTI C_DisablePerception  vtable 0x18237fe30  size 0x28  base C_Node  ctx S_DisablePerceptionContext
struct S_DisablePerceptionContext;
class C_DisablePerception : public C_NodeWrapper<C_DisablePerception, C_Node, S_DisablePerceptionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DisablePerception) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
