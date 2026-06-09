#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CompanionModeGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <CompanionModeGate>  RTTI C_CompanionModeGate  vtable 0x18231caf8  size 0x30  base C_NPCPassiveBarrier  ctx S_CompanionModeGateContext
struct S_CompanionModeGateContext;
class C_CompanionModeGate : public C_NodeWrapper<C_CompanionModeGate, C_NPCPassiveBarrier, S_CompanionModeGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CompanionModeGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_CompanionModeGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
