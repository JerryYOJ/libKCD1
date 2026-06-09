#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnMeleeInactivity>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnMeleeInactivity>  RTTI C_OnMeleeInactivity  vtable 0x182351cf8  size 0x30  base C_CombatantHubExtended<C_ExecutionBarrier>  ctx S_OnMeleeInactivityContext
struct S_OnMeleeInactivityContext;
class C_OnMeleeInactivity : public C_NodeWrapper<C_OnMeleeInactivity, C_CombatantHubExtended<C_ExecutionBarrier>, S_OnMeleeInactivityContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnMeleeInactivity;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnMeleeInactivity) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
