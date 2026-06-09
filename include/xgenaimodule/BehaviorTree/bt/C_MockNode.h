#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MockNode>.

namespace wh::xgenaimodule::BehaviorTree {

// <MockNode>  RTTI C_MockNode  vtable 0x182391fe0  size 0x28  base C_Node  ctx S_MockNodeContext
struct S_MockNodeContext;
class C_MockNode : public C_NodeWrapper<C_MockNode, C_Node, S_MockNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MockNode;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MockNode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
