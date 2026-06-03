#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AngrynessNodeBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetAngryness>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetAngryness>  RTTI C_SetAngryness  vtable 0x1823884c8  size 0x28  base C_AngrynessNodeBase  ctx S_SetAngrynessContext
struct S_SetAngrynessContext;
class C_SetAngryness : public C_NodeWrapper<C_SetAngryness, C_AngrynessNodeBase, S_SetAngrynessContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetAngryness) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
