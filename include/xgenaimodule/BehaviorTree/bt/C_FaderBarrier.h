#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FaderBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <FaderBarrier>  RTTI C_FaderBarrier  vtable 0x18235ee70  size 0x30  base C_DeferredExecution  ctx S_FaderBarrierContext
struct S_FaderBarrierContext;
class C_FaderBarrier : public C_NodeWrapper<C_FaderBarrier, C_DeferredExecution, S_FaderBarrierContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FaderBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
