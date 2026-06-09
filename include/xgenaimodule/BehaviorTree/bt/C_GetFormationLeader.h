#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetFormationLeader>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetFormationLeader>  RTTI C_GetFormationLeader  vtable 0x18236fb48  size 0x28  base C_Node  ctx S_GetFormationLeaderContext
struct S_GetFormationLeaderContext;
class C_GetFormationLeader : public C_NodeWrapper<C_GetFormationLeader, C_Node, S_GetFormationLeaderContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetFormationLeader;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetFormationLeader) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
