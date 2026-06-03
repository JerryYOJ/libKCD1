#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BowShoot>.

namespace wh::xgenaimodule::BehaviorTree {

// <BowShoot>  RTTI C_BowShoot  vtable 0x182345cb8  size 0x28  base C_Node  ctx S_BowShootContext
struct S_BowShootContext;
class C_BowShoot : public C_NodeWrapper<C_BowShoot, C_Node, S_BowShootContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_BowShoot) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
