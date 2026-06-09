#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "C_CombatantHubExtended.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeTutorialSlotAction>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeTutorialSlotAction>  RTTI C_MeleeTutorialSlotAction  vtable 0x182352618  size 0x30  base C_CombatantHubExtended<C_DeferredExecution>  ctx S_MeleeTutorialSlotActionContext
struct S_MeleeTutorialSlotActionContext;
class C_MeleeTutorialSlotAction : public C_NodeWrapper<C_MeleeTutorialSlotAction, C_CombatantHubExtended<C_DeferredExecution>, S_MeleeTutorialSlotActionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MeleeTutorialSlotAction;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_MeleeTutorialSlotAction) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
