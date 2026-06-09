#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FinishPatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <FinishPatch>  RTTI C_FinishPatch  vtable 0x18238b1b8  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_FinishPatch : public C_NodeWrapper<C_FinishPatch, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FinishPatch;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_FinishPatch) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
