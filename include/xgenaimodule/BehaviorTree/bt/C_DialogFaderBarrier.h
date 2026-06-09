#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DialogFaderBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <DialogFaderBarrier>  RTTI C_DialogFaderBarrier  vtable 0x18235f928  size 0x30  base C_DeferredExecution  ctx S_DialogFaderBarrierContext
struct S_DialogFaderBarrierContext;
class C_DialogFaderBarrier : public C_NodeWrapper<C_DialogFaderBarrier, C_DeferredExecution, S_DialogFaderBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DialogFaderBarrier;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DialogFaderBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
