#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Concatenation>.

namespace wh::xgenaimodule::BehaviorTree {

// <Concatenation>  RTTI C_Concatenation  vtable 0x1821fb3c8  size 0x28  base C_Node  ctx S_ConcatenationContext
struct S_ConcatenationContext;
class C_Concatenation : public C_NodeWrapper<C_Concatenation, C_Node, S_ConcatenationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Concatenation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
