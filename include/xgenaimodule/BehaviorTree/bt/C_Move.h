#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_MoveBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Move>.

namespace wh::xgenaimodule::BehaviorTree {

// <Move>  RTTI C_Move  vtable 0x1821d15a0  size 0x30  base C_MoveBase  ctx S_MoveContext
struct S_MoveContext;
class C_Move : public C_NodeWrapper<C_Move, C_MoveBase, S_MoveContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_MoveBase (0x28)
};
static_assert(sizeof(C_Move) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
