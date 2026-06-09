#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ManualSweetSpotBias>.

namespace wh::xgenaimodule::BehaviorTree {

// <ManualSweetSpotBias>  RTTI C_ManualSweetSpotBias  vtable 0x18236e0b0  size 0x28  base C_Node  ctx S_ManualSweetSpotBiasContext
struct S_ManualSweetSpotBiasContext;
class C_ManualSweetSpotBias : public C_NodeWrapper<C_ManualSweetSpotBias, C_Node, S_ManualSweetSpotBiasContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ManualSweetSpotBias;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ManualSweetSpotBias) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
