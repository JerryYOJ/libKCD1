#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeOffenseAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeOffenseAutomation>  RTTI C_MeleeOffenseAutomation  vtable 0x1821f6f10  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MeleeOffenseAutomationContext
struct S_MeleeOffenseAutomationContext;
class C_MeleeOffenseAutomation : public C_NodeWrapper<C_MeleeOffenseAutomation, C_CombatAutomationBase<C_Node>, S_MeleeOffenseAutomationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MeleeOffenseAutomation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MeleeOffenseAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
