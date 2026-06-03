#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetAreaInhabitants>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetAreaInhabitants>  RTTI C_GetAreaInhabitants  vtable 0x1823935c0  size 0x28  base C_Node  ctx S_GetAreaInhabitantsContext
struct S_GetAreaInhabitantsContext;
class C_GetAreaInhabitants : public C_NodeWrapper<C_GetAreaInhabitants, C_Node, S_GetAreaInhabitantsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetAreaInhabitants) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
