#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantDrawWeapon.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DrawWeapon>.

namespace wh::xgenaimodule::BehaviorTree {

// <DrawWeapon>  RTTI C_DrawWeapon  vtable 0x182209278  size 0x28  base C_InstantDrawWeapon<C_AnimatedAction<C_ItemAIAnimAction>>  ctx S_DrawWeaponContext
struct S_DrawWeaponContext;
class C_DrawWeapon : public C_NodeWrapper<C_DrawWeapon, C_InstantDrawWeapon<C_AnimatedAction<C_ItemAIAnimAction>>, S_DrawWeaponContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DrawWeapon) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
