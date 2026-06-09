#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeGuardAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeGuardAutomation>  RTTI C_MeleeGuardAutomation  vtable 0x1821f9658  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeGuardAutomationContext
struct S_MeleeGuardAutomationContext;
class C_MeleeGuardAutomation : public C_NodeWrapper<C_MeleeGuardAutomation, C_CombatAutomationBase<C_Node>, S_MeleeGuardAutomationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MeleeGuardAutomation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeGuardAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
