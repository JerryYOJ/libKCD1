#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetCompanions>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetCompanions>  RTTI C_GetCompanions  vtable 0x182215228  size 0x28  base C_Node  ctx S_GetCompanionsContext
struct S_GetCompanionsContext;
class C_GetCompanions : public C_NodeWrapper<C_GetCompanions, C_Node, S_GetCompanionsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetCompanions) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
