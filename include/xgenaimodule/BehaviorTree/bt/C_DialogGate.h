#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DialogGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <DialogGate>  RTTI C_DialogGate  vtable 0x1821e0ff8  size 0x30  base C_PassiveBarrier  ctx S_DialogGateContext
struct S_DialogGateContext;
class C_DialogGate : public C_NodeWrapper<C_DialogGate, C_PassiveBarrier, S_DialogGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DialogGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DialogGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
