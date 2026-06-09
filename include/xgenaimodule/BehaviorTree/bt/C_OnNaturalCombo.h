#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnNaturalCombo>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnNaturalCombo>  RTTI C_OnNaturalCombo  vtable 0x182351960  size 0x30  base C_CombatantHubExtended<C_PassiveBarrier>  ctx S_OnNaturalComboContext
struct S_OnNaturalComboContext;
class C_OnNaturalCombo : public C_NodeWrapper<C_OnNaturalCombo, C_CombatantHubExtended<C_PassiveBarrier>, S_OnNaturalComboContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnNaturalCombo;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnNaturalCombo) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
