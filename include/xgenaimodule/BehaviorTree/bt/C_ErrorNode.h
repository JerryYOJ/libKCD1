#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ErrorNode>.

namespace wh::xgenaimodule::BehaviorTree {

// <ErrorNode>  RTTI C_ErrorNode  vtable 0x1821fe8a8  size 0x28  base C_Node  ctx S_ErrorNodeContext
struct S_ErrorNodeContext;
class C_ErrorNode : public C_NodeWrapper<C_ErrorNode, C_Node, S_ErrorNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ErrorNode;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ErrorNode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
