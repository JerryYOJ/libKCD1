#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockNode.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantExternalLock>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantExternalLock>  RTTI C_InstantExternalLock  vtable 0x18221af40  size 0x30  base C_LockNode<C_ExecutionBarrier>  ctx S_InstantExternalLockContext
struct S_InstantExternalLockContext;
class C_InstantExternalLock : public C_NodeWrapper<C_InstantExternalLock, C_LockNode<C_ExecutionBarrier>, S_InstantExternalLockContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantExternalLock;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_InstantExternalLock) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
