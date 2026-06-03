#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetKnownInformationsFromGroup>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetKnownInformationsFromGroup>  RTTI C_GetKnownInformationsFromGroup  vtable 0x182375348  size 0x28  base C_Node  ctx S_GetKnownInformationsFromGroupContext
struct S_GetKnownInformationsFromGroupContext;
class C_GetKnownInformationsFromGroup : public C_NodeWrapper<C_GetKnownInformationsFromGroup, C_Node, S_GetKnownInformationsFromGroupContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetKnownInformationsFromGroup) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
