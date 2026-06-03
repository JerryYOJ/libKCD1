#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetCiviliansForLocation>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetCiviliansForLocation>  RTTI C_GetCiviliansForLocation  vtable 0x182389778  size 0x28  base C_Node  ctx S_GetCiviliansForLocationContext
struct S_GetCiviliansForLocationContext;
class C_GetCiviliansForLocation : public C_NodeWrapper<C_GetCiviliansForLocation, C_Node, S_GetCiviliansForLocationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetCiviliansForLocation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
