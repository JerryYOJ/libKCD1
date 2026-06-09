#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GameModeCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <GameModeCondition>  RTTI C_GameModeCondition  vtable 0x1823238e8  size 0x68  base C_Gate  ctx S_GameModeConditionContext
struct S_GameModeConditionContext;
class C_GameModeCondition : public C_NodeWrapper<C_GameModeCondition, C_Gate, S_GameModeConditionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GameModeCondition;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_GameModeCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
