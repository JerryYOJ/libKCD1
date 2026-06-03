#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GameOver>.

namespace wh::xgenaimodule::BehaviorTree {

// <GameOver>  RTTI C_GameOver  vtable 0x182389db0  size 0x28  base C_Node  ctx S_GameOverContext
struct S_GameOverContext;
class C_GameOver : public C_NodeWrapper<C_GameOver, C_Node, S_GameOverContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GameOver) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
