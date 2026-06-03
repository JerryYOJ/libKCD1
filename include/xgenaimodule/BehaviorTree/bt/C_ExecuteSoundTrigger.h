#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ExecuteSoundTrigger>.

namespace wh::xgenaimodule::BehaviorTree {

// <ExecuteSoundTrigger>  RTTI C_ExecuteSoundTrigger  vtable 0x182221010  size 0x28  base C_Node  ctx S_ExecuteSoundTriggerContext
struct S_ExecuteSoundTriggerContext;
class C_ExecuteSoundTrigger : public C_NodeWrapper<C_ExecuteSoundTrigger, C_Node, S_ExecuteSoundTriggerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ExecuteSoundTrigger) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
