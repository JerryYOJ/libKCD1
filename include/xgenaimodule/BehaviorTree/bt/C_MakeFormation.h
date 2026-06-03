#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MakeFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MakeFormation>  RTTI C_MakeFormation  vtable 0x18236e1b0  size 0x28  base C_Node  ctx S_MakeFormationContext
struct S_MakeFormationContext;
class C_MakeFormation : public C_NodeWrapper<C_MakeFormation, C_Node, S_MakeFormationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MakeFormation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
