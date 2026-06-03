#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeShoutAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeShoutAutomation>  RTTI C_MeleeShoutAutomation  vtable 0x1821f6540  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeShoutAutomation
struct S_MeleeShoutAutomation;
class C_MeleeShoutAutomation : public C_NodeWrapper<C_MeleeShoutAutomation, C_CombatAutomationBase<C_Node>, S_MeleeShoutAutomation>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeShoutAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
