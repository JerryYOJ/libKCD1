#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsNightTimeOfDay>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsNightTimeOfDay>  RTTI C_IsNightTimeOfDay  vtable 0x18235d3a0  size 0x68  base C_Gate  ctx S_GateContext
struct S_GateContext;
class C_IsNightTimeOfDay : public C_NodeWrapper<C_IsNightTimeOfDay, C_Gate, S_GateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsNightTimeOfDay;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsNightTimeOfDay) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
