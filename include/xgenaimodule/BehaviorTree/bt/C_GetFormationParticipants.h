#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetFormationParticipants>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetFormationParticipants>  RTTI C_GetFormationParticipants  vtable 0x18236f580  size 0x28  base C_Node  ctx S_GetFormationParticipantsContext
struct S_GetFormationParticipantsContext;
class C_GetFormationParticipants : public C_NodeWrapper<C_GetFormationParticipants, C_Node, S_GetFormationParticipantsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetFormationParticipants) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
