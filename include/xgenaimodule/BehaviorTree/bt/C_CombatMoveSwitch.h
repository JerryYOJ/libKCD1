#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "C_ForwardingData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CombatMoveSwitch>.

namespace wh::xgenaimodule::BehaviorTree {

// <CombatMoveSwitch>  RTTI C_CombatMoveSwitch  vtable 0x182213f60  size 0x58  base C_ForwardingData<C_FixedComposite<2>>  ctx S_CombatMoveSwitchContext
struct S_CombatMoveSwitchContext;
class C_CombatMoveSwitch : public C_NodeWrapper<C_CombatMoveSwitch, C_ForwardingData<C_FixedComposite<2>>, S_CombatMoveSwitchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatMoveSwitch;
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_ForwardingData<C_FixedComposite<2>> (0x38)
};
static_assert(sizeof(C_CombatMoveSwitch) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
