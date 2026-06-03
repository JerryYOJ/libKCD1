#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsEnemy>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsEnemy>  RTTI C_IsEnemy  vtable 0x182201150  size 0x28  base C_Node  ctx S_IsEnemyContext
struct S_IsEnemyContext;
class C_IsEnemy : public C_NodeWrapper<C_IsEnemy, C_Node, S_IsEnemyContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_IsEnemy) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
