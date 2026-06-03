#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopMinigame>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopMinigame>  RTTI C_StopMinigame  vtable 0x182348520  size 0x28  base C_Node  ctx S_StopMinigameContext
struct S_StopMinigameContext;
class C_StopMinigame : public C_NodeWrapper<C_StopMinigame, C_Node, S_StopMinigameContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopMinigame) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
