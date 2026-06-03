#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeDefenseAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeDefenseAutomation>  RTTI C_MeleeDefenseAutomation  vtable 0x1821f98d0  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeDefenseAutomationContext
struct S_MeleeDefenseAutomationContext;
class C_MeleeDefenseAutomation : public C_NodeWrapper<C_MeleeDefenseAutomation, C_CombatAutomationBase<C_Node>, S_MeleeDefenseAutomationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeDefenseAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
