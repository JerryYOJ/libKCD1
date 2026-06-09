#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetOnLadder>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetOnLadder>  RTTI C_GetOnLadder  vtable 0x182225178  size 0x28  base C_Node  ctx S_GetOnLadderContext
struct S_GetOnLadderContext;
class C_GetOnLadder : public C_NodeWrapper<C_GetOnLadder, C_Node, S_GetOnLadderContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetOnLadder;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetOnLadder) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
