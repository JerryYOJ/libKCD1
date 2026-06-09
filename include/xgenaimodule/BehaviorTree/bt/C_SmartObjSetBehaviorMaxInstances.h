#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SmartObjSetBehaviorMaxInstances>.

namespace wh::xgenaimodule::BehaviorTree {

// <SmartObjSetBehaviorMaxInstances>  RTTI C_SmartObjSetBehaviorMaxInstances  vtable 0x182210d08  size 0x28  base C_Node  ctx S_SmartObjSetBehaviorMaxInstancesContext
struct S_SmartObjSetBehaviorMaxInstancesContext;
class C_SmartObjSetBehaviorMaxInstances : public C_NodeWrapper<C_SmartObjSetBehaviorMaxInstances, C_Node, S_SmartObjSetBehaviorMaxInstancesContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SmartObjSetBehaviorMaxInstances;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SmartObjSetBehaviorMaxInstances) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
