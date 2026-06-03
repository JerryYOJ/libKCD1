#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_IfCondition.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <WeatherCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <WeatherCondition>  RTTI C_WeatherCondition  vtable 0x1826f6268  size 0x48  base C_IfCondition  ctx S_WeatherConditionContext
struct S_WeatherConditionContext;
class C_WeatherCondition : public C_NodeWrapper<C_WeatherCondition, C_IfCondition, S_WeatherConditionContext>
{
    // no own data members (object == 0x48)
};
static_assert(sizeof(C_WeatherCondition) == 0x48);

}  // namespace wh::xgenaimodule::BehaviorTree
