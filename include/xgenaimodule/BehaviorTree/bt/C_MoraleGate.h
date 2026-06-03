#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStatGateBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MoraleGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <MoraleGate>  RTTI C_MoraleGate  vtable 0x18236c2c8  size 0x30  base C_NPCStatGateBase  ctx S_NPCStateGateBaseContext
struct S_NPCStateGateBaseContext;
class C_MoraleGate : public C_NodeWrapper<C_MoraleGate, C_NPCStatGateBase, S_NPCStateGateBaseContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_MoraleGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
