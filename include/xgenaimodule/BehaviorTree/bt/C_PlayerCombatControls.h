#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerCombatControls>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerCombatControls>  RTTI C_PlayerCombatControls  vtable 0x182350c00  size 0x28  base C_Node  ctx S_PlayerCombatControlsContext
struct S_PlayerCombatControlsContext;
class C_PlayerCombatControls : public C_NodeWrapper<C_PlayerCombatControls, C_Node, S_PlayerCombatControlsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PlayerCombatControls) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
