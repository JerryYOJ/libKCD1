#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetLadder>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetLadder>  RTTI C_GetLadder  vtable 0x182333050  size 0x28  base C_Node  ctx S_GetLadderContext
struct S_GetLadderContext;
class C_GetLadder : public C_NodeWrapper<C_GetLadder, C_Node, S_GetLadderContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetLadder;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetLadder) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
