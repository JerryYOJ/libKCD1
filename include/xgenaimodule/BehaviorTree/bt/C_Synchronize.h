#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockBarrier.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Synchronize>.

namespace wh::xgenaimodule::BehaviorTree {

// <Synchronize>  RTTI C_Synchronize  vtable 0x1821e0ac8  size 0x30  base C_LockBarrier<C_ExecutionBarrier>  ctx S_SynchronizeContext
struct S_SynchronizeContext;
class C_Synchronize : public C_NodeWrapper<C_Synchronize, C_LockBarrier<C_ExecutionBarrier>, S_SynchronizeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Synchronize;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Synchronize) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
