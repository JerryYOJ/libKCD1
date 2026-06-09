#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Success>.

namespace wh::xgenaimodule::BehaviorTree {

// <Success>  RTTI C_Success  vtable 0x1821c29b8  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_Success : public C_NodeWrapper<C_Success, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Success;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Success) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
