#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddGameContext>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddGameContext>  RTTI C_AddGameContext  vtable 0x182324068  size 0x28  base C_Node  ctx S_GameContext
struct S_GameContext;
class C_AddGameContext : public C_NodeWrapper<C_AddGameContext, C_Node, S_GameContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddGameContext) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
