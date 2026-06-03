#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Revive>.

namespace wh::xgenaimodule::BehaviorTree {

// <Revive>  RTTI C_Revive  vtable 0x18233be38  size 0x28  base C_Node  ctx S_ReviveContext
struct S_ReviveContext;
class C_Revive : public C_NodeWrapper<C_Revive, C_Node, S_ReviveContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Revive) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
