#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetMemberFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetMemberFormation>  RTTI C_GetMemberFormation  vtable 0x18236e178  size 0x28  base C_Node  ctx S_GetMemberFormationContext
struct S_GetMemberFormationContext;
class C_GetMemberFormation : public C_NodeWrapper<C_GetMemberFormation, C_Node, S_GetMemberFormationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetMemberFormation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetMemberFormation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
