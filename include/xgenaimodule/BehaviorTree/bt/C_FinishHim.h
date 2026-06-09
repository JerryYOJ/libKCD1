#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FinishHim>.

namespace wh::xgenaimodule::BehaviorTree {

// <FinishHim>  RTTI C_FinishHim  vtable 0x182324768  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_FinishHim : public C_NodeWrapper<C_FinishHim, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FinishHim;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_FinishHim) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
