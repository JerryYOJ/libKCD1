#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FixedPositionLODBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <FixedPositionLODBarrier>  RTTI C_FixedPositionLODBarrier  vtable 0x18236c598  size 0x30  base C_PassiveBarrier  ctx S_FixedPositionLODBarrierContext
struct S_FixedPositionLODBarrierContext;
class C_FixedPositionLODBarrier : public C_NodeWrapper<C_FixedPositionLODBarrier, C_PassiveBarrier, S_FixedPositionLODBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FixedPositionLODBarrier;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FixedPositionLODBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
