#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetLockParticipants>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetLockParticipants>  RTTI C_GetLockParticipants  vtable 0x18232d400  size 0x28  base C_Node  ctx S_GetLockParticipantsContext
struct S_GetLockParticipantsContext;
class C_GetLockParticipants : public C_NodeWrapper<C_GetLockParticipants, C_Node, S_GetLockParticipantsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetLockParticipants) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
