#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerMove>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerMove>  RTTI C_PlayerMove  vtable 0x18233e788  size 0x28  base C_DefferedStateChange  ctx S_PlayerMoveContext
struct S_PlayerMoveContext;
class C_PlayerMove : public C_NodeWrapper<C_PlayerMove, C_DefferedStateChange, S_PlayerMoveContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PlayerMove) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
