#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStatGateBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NPCStateGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <NPCStateGate>  RTTI C_NPCStateGate  vtable 0x1822194c0  size 0x30  base C_NPCStatGateBase  ctx S_NPCStateGateContext
struct S_NPCStateGateContext;
class C_NPCStateGate : public C_NodeWrapper<C_NPCStateGate, C_NPCStatGateBase, S_NPCStateGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NPCStateGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_NPCStateGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
