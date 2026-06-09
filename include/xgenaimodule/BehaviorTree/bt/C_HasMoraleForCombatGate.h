#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NpcStateGateBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasMoraleForCombatGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasMoraleForCombatGate>  RTTI C_HasMoraleForCombatGate  vtable 0x1821e5358  size 0x30  base C_NpcStateGateBase  ctx S_NpcStateGateBaseContext
struct S_NpcStateGateBaseContext;
class C_HasMoraleForCombatGate : public C_NodeWrapper<C_HasMoraleForCombatGate, C_NpcStateGateBase, S_NpcStateGateBaseContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HasMoraleForCombatGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_HasMoraleForCombatGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
