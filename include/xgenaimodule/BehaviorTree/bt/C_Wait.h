#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Wait>.

namespace wh::xgenaimodule::BehaviorTree {

// <Wait>  RTTI C_Wait  vtable 0x1821e8de8  size 0x28  base C_Node  ctx S_WaitContext
struct S_WaitContext;
class C_Wait : public C_NodeWrapper<C_Wait, C_Node, S_WaitContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Wait;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Wait) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
