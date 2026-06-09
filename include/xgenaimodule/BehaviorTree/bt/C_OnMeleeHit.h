#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "C_CombatantHubExtended.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnMeleeHit>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnMeleeHit>  RTTI C_OnMeleeHit  vtable 0x1823520c0  size 0x30  base C_CombatantHubExtended<C_DeferredExecution>  ctx S_OnMeleeHitContext
struct S_OnMeleeHitContext;
class C_OnMeleeHit : public C_NodeWrapper<C_OnMeleeHit, C_CombatantHubExtended<C_DeferredExecution>, S_OnMeleeHitContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnMeleeHit;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnMeleeHit) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
