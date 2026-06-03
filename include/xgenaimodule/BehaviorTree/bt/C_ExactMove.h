#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_MoveBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ExactMove>.

namespace wh::xgenaimodule::BehaviorTree {

// <ExactMove>  RTTI C_ExactMove  vtable 0x1821d1ba0  size 0x38  base C_ForwardingData<C_MoveBase>  ctx S_ExactMoveContext
struct S_ExactMoveContext;
class C_ExactMove : public C_NodeWrapper<C_ExactMove, C_ForwardingData<C_MoveBase>, S_ExactMoveContext>
{
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_ForwardingData<C_MoveBase> (0x28)
};
static_assert(sizeof(C_ExactMove) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
