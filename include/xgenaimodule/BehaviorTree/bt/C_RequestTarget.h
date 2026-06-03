#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RequestTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <RequestTarget>  RTTI C_RequestTarget  vtable 0x182357e60  size 0x28  base C_CombatNode<C_DefferedStateChange>  ctx S_RequestTargetContext
struct S_RequestTargetContext;
class C_RequestTarget : public C_NodeWrapper<C_RequestTarget, C_CombatNode<C_DefferedStateChange>, S_RequestTargetContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RequestTarget) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
