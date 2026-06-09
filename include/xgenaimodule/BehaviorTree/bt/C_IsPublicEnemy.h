#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsPublicEnemy>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsPublicEnemy>  RTTI C_IsPublicEnemy  vtable 0x18219c040  size 0x68  base C_Gate  ctx S_IsPublicEnemyContext
struct S_IsPublicEnemyContext;
class C_IsPublicEnemy : public C_NodeWrapper<C_IsPublicEnemy, C_Gate, S_IsPublicEnemyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsPublicEnemy;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsPublicEnemy) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
