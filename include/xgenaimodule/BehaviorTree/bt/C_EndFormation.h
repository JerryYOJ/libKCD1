#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EndFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <EndFormation>  RTTI C_EndFormation  vtable 0x1823701e0  size 0x28  base C_Node  ctx S_EndFormationContext
struct S_EndFormationContext;
class C_EndFormation : public C_NodeWrapper<C_EndFormation, C_Node, S_EndFormationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EndFormation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_EndFormation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
