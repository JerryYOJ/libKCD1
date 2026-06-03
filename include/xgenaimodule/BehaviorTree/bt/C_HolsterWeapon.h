#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantHolsterWeapon.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HolsterWeapon>.

namespace wh::xgenaimodule::BehaviorTree {

// <HolsterWeapon>  RTTI C_HolsterWeapon  vtable 0x182219f98  size 0x28  base C_InstantHolsterWeapon<C_AnimatedAction<C_HolsterItemAnimAction>>  ctx S_BaseNodeContext
class C_HolsterWeapon : public C_NodeWrapper<C_HolsterWeapon, C_InstantHolsterWeapon<C_AnimatedAction<C_HolsterItemAnimAction>>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_HolsterWeapon) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
