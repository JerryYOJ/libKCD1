#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetSituationState>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetSituationState>  RTTI C_SetSituationState  vtable 0x182391a18  size 0x28  base C_Node  ctx S_SetSituationStateContext
struct S_SetSituationStateContext;
class C_SetSituationState : public C_NodeWrapper<C_SetSituationState, C_Node, S_SetSituationStateContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetSituationState) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
