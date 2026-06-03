#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CreateInformation>.

namespace wh::xgenaimodule::BehaviorTree {

// <CreateInformation>  RTTI C_CreateInformation  vtable 0x182211f90  size 0x28  base C_Node  ctx S_CreateInformationContext
struct S_CreateInformationContext;
class C_CreateInformation : public C_NodeWrapper<C_CreateInformation, C_Node, S_CreateInformationContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CreateInformation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
