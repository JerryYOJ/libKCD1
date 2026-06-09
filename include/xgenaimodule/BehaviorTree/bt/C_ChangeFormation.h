#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ChangeFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <ChangeFormation>  RTTI C_ChangeFormation  vtable 0x1823636a0  size 0x28  base C_Node  ctx S_ChangeFormationContext
struct S_ChangeFormationContext;
class C_ChangeFormation : public C_NodeWrapper<C_ChangeFormation, C_Node, S_ChangeFormationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ChangeFormation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ChangeFormation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
