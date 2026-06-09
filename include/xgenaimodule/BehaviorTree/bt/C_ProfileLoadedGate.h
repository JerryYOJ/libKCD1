#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ProfileLoadedGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <ProfileLoadedGate>  RTTI C_ProfileLoadedGate  vtable 0x18236b808  size 0x30  base C_PassiveBarrier  ctx S_ProfileLoadedGateContext
struct S_ProfileLoadedGateContext;
class C_ProfileLoadedGate : public C_NodeWrapper<C_ProfileLoadedGate, C_PassiveBarrier, S_ProfileLoadedGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ProfileLoadedGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ProfileLoadedGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
