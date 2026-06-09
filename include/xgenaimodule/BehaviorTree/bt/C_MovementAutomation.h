#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatAutomationBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MovementAutomation>.

namespace wh::xgenaimodule::BehaviorTree {

// <MovementAutomation>  RTTI C_MovementAutomation  vtable 0x1821f7188  size 0x28  base C_CombatAutomationBase<C_Node>  ctx S_MovementAutomationContext
struct S_MovementAutomationContext;
class C_MovementAutomation : public C_NodeWrapper<C_MovementAutomation, C_CombatAutomationBase<C_Node>, S_MovementAutomationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MovementAutomation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MovementAutomation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
