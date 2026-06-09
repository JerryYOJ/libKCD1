#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Switch>.

namespace wh::xgenaimodule::BehaviorTree {

// <Switch>  RTTI C_Switch  vtable ?  size 0x60  base C_SwitchBase  ctx S_SwitchBaseContext
struct S_SwitchBaseContext;
class C_Switch : public C_NodeWrapper<C_Switch, C_SwitchBase, S_SwitchBaseContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Switch;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_SwitchBase (0x58)
};
static_assert(sizeof(C_Switch) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
