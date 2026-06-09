#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeDefenseAutomationControls>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeDefenseAutomationControls>  RTTI C_MeleeDefenseAutomationControls  vtable 0x1823537b8  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeDefenseAutomationControlsContext
struct S_MeleeDefenseAutomationControlsContext;
class C_MeleeDefenseAutomationControls : public C_NodeWrapper<C_MeleeDefenseAutomationControls, C_CombatAutomationBase<C_Node>, S_MeleeDefenseAutomationControlsContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MeleeDefenseAutomationControls;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeDefenseAutomationControls) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
