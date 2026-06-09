#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ProbablisticDrivenSweetSpot>.

namespace wh::xgenaimodule::BehaviorTree {

// <ProbablisticDrivenSweetSpot>  RTTI C_ProbablisticDrivenSweetSpot  vtable 0x182225c58  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_ProbablisticDrivenSweetSpot : public C_NodeWrapper<C_ProbablisticDrivenSweetSpot, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ProbablisticDrivenSweetSpot;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ProbablisticDrivenSweetSpot) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
