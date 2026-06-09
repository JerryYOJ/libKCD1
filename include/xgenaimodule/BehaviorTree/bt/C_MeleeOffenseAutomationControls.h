#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeOffenseAutomationControls>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeOffenseAutomationControls>  RTTI C_MeleeOffenseAutomationControls  vtable 0x1821f93e0  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeOffenseAutomationControlsContext
struct S_MeleeOffenseAutomationControlsContext;
class C_MeleeOffenseAutomationControls : public C_NodeWrapper<C_MeleeOffenseAutomationControls, C_CombatAutomationBase<C_Node>, S_MeleeOffenseAutomationControlsContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MeleeOffenseAutomationControls;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeOffenseAutomationControls) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
