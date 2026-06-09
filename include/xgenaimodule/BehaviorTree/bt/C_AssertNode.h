#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AssertNode>.

namespace wh::xgenaimodule::BehaviorTree {

// <AssertNode>  RTTI C_AssertNode  vtable 0x18231d8b0  size 0x28  base C_Node  ctx S_AssertNodeContext
struct S_AssertNodeContext;
class C_AssertNode : public C_NodeWrapper<C_AssertNode, C_Node, S_AssertNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AssertNode;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AssertNode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
