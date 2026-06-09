#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClimbLadder>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClimbLadder>  RTTI C_ClimbLadder  vtable 0x18220bb60  size 0x28  base C_CombatAutomationBase<C_DefferedStateChange>  ctx S_ClimbLadderContext
struct S_ClimbLadderContext;
class C_ClimbLadder : public C_NodeWrapper<C_ClimbLadder, C_CombatAutomationBase<C_DefferedStateChange>, S_ClimbLadderContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ClimbLadder;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClimbLadder) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
