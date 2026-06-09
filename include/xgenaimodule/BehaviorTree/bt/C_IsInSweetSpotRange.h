#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsInSweetSpotRange>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsInSweetSpotRange>  RTTI C_IsInSweetSpotRange  vtable 0x182353070  size 0x30  base C_ActiveBarrier  ctx S_IsInSweetSpotRangeContext
struct S_IsInSweetSpotRangeContext;
class C_IsInSweetSpotRange : public C_NodeWrapper<C_IsInSweetSpotRange, C_ActiveBarrier, S_IsInSweetSpotRangeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsInSweetSpotRange;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IsInSweetSpotRange) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
