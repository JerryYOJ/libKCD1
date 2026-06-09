#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SwitchLevel>.

namespace wh::xgenaimodule::BehaviorTree {

// <SwitchLevel>  RTTI C_SwitchLevel  vtable 0x182348558  size 0x28  base C_DefferedStateChange  ctx S_SwitchLevelContext
struct S_SwitchLevelContext;
class C_SwitchLevel : public C_NodeWrapper<C_SwitchLevel, C_DefferedStateChange, S_SwitchLevelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SwitchLevel;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SwitchLevel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
