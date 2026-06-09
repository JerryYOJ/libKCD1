#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IfCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <IfCondition>  RTTI C_IfCondition  vtable 0x1821c1618  size 0x48  base C_Decorator  ctx S_IfConditionContext
struct S_IfConditionContext;
class C_IfCondition : public C_NodeWrapper<C_IfCondition, C_Decorator, S_IfConditionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IfCondition;
    uint8_t _ownState[0x18];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_IfCondition) == 0x48);

}  // namespace wh::xgenaimodule::BehaviorTree
