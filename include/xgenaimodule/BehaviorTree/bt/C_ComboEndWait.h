#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ComboEndWait>.

namespace wh::xgenaimodule::BehaviorTree {

// <ComboEndWait>  RTTI C_ComboEndWait  vtable 0x1823543c8  size 0x28  base C_CombatantHubExtended<C_DefferedStateChange>  ctx S_ComboEndWaitContext
struct S_ComboEndWaitContext;
class C_ComboEndWait : public C_NodeWrapper<C_ComboEndWait, C_CombatantHubExtended<C_DefferedStateChange>, S_ComboEndWaitContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ComboEndWait) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
