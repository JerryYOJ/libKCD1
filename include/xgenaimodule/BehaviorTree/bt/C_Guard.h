#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Guard>.

namespace wh::xgenaimodule::BehaviorTree {

// <Guard>  RTTI C_Guard  vtable 0x182353e08  size 0x30  base C_CombatNode<C_PassiveBarrier>  ctx S_GuardContext
struct S_GuardContext;
class C_Guard : public C_NodeWrapper<C_Guard, C_CombatNode<C_PassiveBarrier>, S_GuardContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Guard) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
