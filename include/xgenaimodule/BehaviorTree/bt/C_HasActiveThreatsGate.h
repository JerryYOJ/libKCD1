#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NpcStateGateBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasActiveThreatsGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasActiveThreatsGate>  RTTI C_HasActiveThreatsGate  vtable 0x182389528  size 0x30  base C_NpcStateGateBase  ctx S_NpcStateGateBaseContext
struct S_NpcStateGateBaseContext;
class C_HasActiveThreatsGate : public C_NodeWrapper<C_HasActiveThreatsGate, C_NpcStateGateBase, S_NpcStateGateBaseContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HasActiveThreatsGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_HasActiveThreatsGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
