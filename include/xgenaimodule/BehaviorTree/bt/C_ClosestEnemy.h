#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClosestEnemy>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClosestEnemy>  RTTI C_ClosestEnemy  vtable 0x1823581f8  size 0x30  base C_Decorator  ctx S_ClosestEnemyContext
struct S_ClosestEnemyContext;
class C_ClosestEnemy : public C_NodeWrapper<C_ClosestEnemy, C_Decorator, S_ClosestEnemyContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ClosestEnemy) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
