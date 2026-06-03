#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BowAim>.

namespace wh::xgenaimodule::BehaviorTree {

// <BowAim>  RTTI C_BowAim  vtable 0x182347170  size 0x28  base C_Node  ctx S_BowAimContext
struct S_BowAimContext;
class C_BowAim : public C_NodeWrapper<C_BowAim, C_Node, S_BowAimContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_BowAim) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
