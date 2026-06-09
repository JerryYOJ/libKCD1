#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockNode.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantSynchronize>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantSynchronize>  RTTI C_InstantSynchronize  vtable 0x182222520  size 0x30  base C_LockNode<C_ExecutionBarrier>  ctx S_InstantSynchronizeContext
struct S_InstantSynchronizeContext;
class C_InstantSynchronize : public C_NodeWrapper<C_InstantSynchronize, C_LockNode<C_ExecutionBarrier>, S_InstantSynchronizeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantSynchronize;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_InstantSynchronize) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
