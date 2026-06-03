#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetIsAimed>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetIsAimed>  RTTI C_SetIsAimed  vtable 0x182350c38  size 0x28  base C_CombatNode<C_Node>  ctx S_SetIsAimedContext
struct S_SetIsAimedContext;
class C_SetIsAimed : public C_NodeWrapper<C_SetIsAimed, C_CombatNode<C_Node>, S_SetIsAimedContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetIsAimed) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
