#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetMaxInstances>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetMaxInstances>  RTTI C_GetMaxInstances  vtable 0x18232d100  size 0x28  base C_Node  ctx S_GetMaxInstancesContext
struct S_GetMaxInstancesContext;
class C_GetMaxInstances : public C_NodeWrapper<C_GetMaxInstances, C_Node, S_GetMaxInstancesContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetMaxInstances;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetMaxInstances) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
