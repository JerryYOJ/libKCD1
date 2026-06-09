#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_OnActionBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnMeleeCombatAction>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnMeleeCombatAction>  RTTI C_OnMeleeCombatAction  vtable 0x182218528  size 0x30  base C_OnActionBase  ctx S_OnMeleeCombatActionContext
struct S_OnMeleeCombatActionContext;
class C_OnMeleeCombatAction : public C_NodeWrapper<C_OnMeleeCombatAction, C_OnActionBase, S_OnMeleeCombatActionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnMeleeCombatAction;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnMeleeCombatAction) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
