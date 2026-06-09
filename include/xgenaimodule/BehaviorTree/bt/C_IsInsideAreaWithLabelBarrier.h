#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsInsideAreaWithLabelBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsInsideAreaWithLabelBarrier>  RTTI C_IsInsideAreaWithLabelBarrier  vtable 0x18221f710  size 0x30  base C_PassiveBarrier  ctx S_IsInsideAreaWithLabelBarrierContext
struct S_IsInsideAreaWithLabelBarrierContext;
class C_IsInsideAreaWithLabelBarrier : public C_NodeWrapper<C_IsInsideAreaWithLabelBarrier, C_PassiveBarrier, S_IsInsideAreaWithLabelBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsInsideAreaWithLabelBarrier;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IsInsideAreaWithLabelBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
