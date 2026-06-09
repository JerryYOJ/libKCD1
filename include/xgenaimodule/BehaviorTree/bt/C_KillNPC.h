#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <KillNPC>.

namespace wh::xgenaimodule::BehaviorTree {

// <KillNPC>  RTTI C_KillNPC  vtable 0x1823333d0  size 0x28  base C_DefferedStateChange  ctx S_KillAnimationContext
struct S_KillAnimationContext;
class C_KillNPC : public C_NodeWrapper<C_KillNPC, C_DefferedStateChange, S_KillAnimationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_KillNPC;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_KillNPC) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
