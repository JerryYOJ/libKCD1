#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_DeferredExecution.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LinkOperationBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <LinkOperationBarrier>  RTTI C_LinkOperationBarrier  vtable 0x1821f49b0  size 0x30  base C_ForwardingData<C_DeferredExecution>  ctx S_LinkOperationBarrierContext
struct S_LinkOperationBarrierContext;
class C_LinkOperationBarrier : public C_NodeWrapper<C_LinkOperationBarrier, C_ForwardingData<C_DeferredExecution>, S_LinkOperationBarrierContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LinkOperationBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
