#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BowCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BowCheckRange>.

namespace wh::xgenaimodule::BehaviorTree {

// <BowCheckRange>  RTTI C_BowCheckRange  vtable 0x182346910  size 0x28  base C_BowCheckBase  ctx S_BowCheckBaseContext
struct S_BowCheckBaseContext;
class C_BowCheckRange : public C_NodeWrapper<C_BowCheckRange, C_BowCheckBase, S_BowCheckBaseContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_BowCheckRange) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
