#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RainGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <RainGate>  RTTI C_RainGate  vtable 0x18236b1f8  size 0x30  base C_PassiveBarrier  ctx S_RainGateContext
struct S_RainGateContext;
class C_RainGate : public C_NodeWrapper<C_RainGate, C_PassiveBarrier, S_RainGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RainGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_RainGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
