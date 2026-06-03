#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetExternalLock>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetExternalLock>  RTTI C_SetExternalLock  vtable 0x18219cec8  size 0x28  base C_Node  ctx S_SetExternalLockContext
struct S_SetExternalLockContext;
class C_SetExternalLock : public C_NodeWrapper<C_SetExternalLock, C_Node, S_SetExternalLockContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetExternalLock) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
