#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ActivateSubbrain>.

namespace wh::xgenaimodule::BehaviorTree {

// <ActivateSubbrain>  RTTI C_ActivateSubbrain  vtable 0x1822116d8  size 0x28  base C_Node  ctx S_ActivateSubbrainContext
struct S_ActivateSubbrainContext;
class C_ActivateSubbrain : public C_NodeWrapper<C_ActivateSubbrain, C_Node, S_ActivateSubbrainContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ActivateSubbrain) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
