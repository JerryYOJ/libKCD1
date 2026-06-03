#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetPlayerHorse>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetPlayerHorse>  RTTI C_GetPlayerHorse  vtable 0x18232ce00  size 0x28  base C_Node  ctx S_GetPlayerHorseContext
struct S_GetPlayerHorseContext;
class C_GetPlayerHorse : public C_NodeWrapper<C_GetPlayerHorse, C_Node, S_GetPlayerHorseContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetPlayerHorse) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
