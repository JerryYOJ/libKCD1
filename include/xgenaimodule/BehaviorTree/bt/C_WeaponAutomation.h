#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_CombatAutomationBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <WeaponAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <WeaponAutomation>  RTTI C_WeaponAutomation  vtable 0x182209cf0  size 0x28  base C_CombatAutomationBase<C_AnimatedAction<C_ItemAIAnimAction>>  ctx S_WeaponAutomationContext
struct S_WeaponAutomationContext;
class C_WeaponAutomation : public C_NodeWrapper<C_WeaponAutomation, C_CombatAutomationBase<C_AnimatedAction<C_ItemAIAnimAction>>, S_WeaponAutomationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_WeaponAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
