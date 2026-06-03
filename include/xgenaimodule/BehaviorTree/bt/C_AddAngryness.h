#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AngrynessNodeBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddAngryness>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddAngryness>  RTTI C_AddAngryness  vtable 0x182388258  size 0x28  base C_AngrynessNodeBase  ctx S_AddAngrynessContext
struct S_AddAngrynessContext;
class C_AddAngryness : public C_NodeWrapper<C_AddAngryness, C_AngrynessNodeBase, S_AddAngrynessContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddAngryness) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
