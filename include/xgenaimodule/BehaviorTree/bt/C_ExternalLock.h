#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockBarrier.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ExternalLock>.

namespace wh::xgenaimodule::BehaviorTree {

// <ExternalLock>  RTTI C_ExternalLock  vtable 0x1821e14e8  size 0x30  base C_LockBarrier<C_ExecutionBarrier>  ctx S_ExternalLockContext
struct S_ExternalLockContext;
class C_ExternalLock : public C_NodeWrapper<C_ExternalLock, C_LockBarrier<C_ExecutionBarrier>, S_ExternalLockContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ExternalLock) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
