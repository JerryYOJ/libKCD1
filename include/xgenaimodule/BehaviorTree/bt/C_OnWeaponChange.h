#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnWeaponChange>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnWeaponChange>  RTTI C_OnWeaponChange  vtable 0x182351458  size 0x30  base C_CombatantHubExtended<C_PassiveBarrier>  ctx S_OnWeaponChangeContext
struct S_OnWeaponChangeContext;
class C_OnWeaponChange : public C_NodeWrapper<C_OnWeaponChange, C_CombatantHubExtended<C_PassiveBarrier>, S_OnWeaponChangeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnWeaponChange;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnWeaponChange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
