#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "C_CombatantHubExtended.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnCombatEvent>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnCombatEvent>  RTTI C_OnCombatEvent  vtable 0x182352c38  size 0x30  base C_CombatantHubExtended<C_DeferredExecution>  ctx S_OnCombatEventContext
struct S_OnCombatEventContext;
class C_OnCombatEvent : public C_NodeWrapper<C_OnCombatEvent, C_CombatantHubExtended<C_DeferredExecution>, S_OnCombatEventContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnCombatEvent;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnCombatEvent) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
