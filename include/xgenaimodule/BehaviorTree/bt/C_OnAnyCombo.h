#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatantHubExtended.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnAnyCombo>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnAnyCombo>  RTTI C_OnAnyCombo  vtable 0x182352310  size 0x30  base C_CombatantHubExtended<C_PassiveBarrier>  ctx S_OnAnyComboContext
struct S_OnAnyComboContext;
class C_OnAnyCombo : public C_NodeWrapper<C_OnAnyCombo, C_CombatantHubExtended<C_PassiveBarrier>, S_OnAnyComboContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnAnyCombo;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnAnyCombo) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
