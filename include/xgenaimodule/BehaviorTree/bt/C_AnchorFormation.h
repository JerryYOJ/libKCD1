#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AnchorFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <AnchorFormation>  RTTI C_AnchorFormation  vtable 0x1823636d8  size 0x30  base C_PassiveBarrier  ctx S_AnchorFormationContext
struct S_AnchorFormationContext;
class C_AnchorFormation : public C_NodeWrapper<C_AnchorFormation, C_PassiveBarrier, S_AnchorFormationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AnchorFormation;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AnchorFormation) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
