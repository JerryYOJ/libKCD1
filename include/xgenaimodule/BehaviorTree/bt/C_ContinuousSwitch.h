#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ContinuousSwitch>.

namespace wh::xgenaimodule::BehaviorTree {

// <ContinuousSwitch>  RTTI C_ContinuousSwitch  vtable 0x1821c49b0  size 0x58  base C_SwitchBase  ctx S_ContinuousSwitchContext
struct S_ContinuousSwitchContext;
class C_ContinuousSwitch : public C_NodeWrapper<C_ContinuousSwitch, C_SwitchBase, S_ContinuousSwitchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ContinuousSwitch;
    // no own data members (object == 0x58)
};
static_assert(sizeof(C_ContinuousSwitch) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
