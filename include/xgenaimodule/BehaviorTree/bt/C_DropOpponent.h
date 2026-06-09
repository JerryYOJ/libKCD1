#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DropOpponent>.

namespace wh::xgenaimodule::BehaviorTree {

// <DropOpponent>  RTTI C_DropOpponent  vtable 0x1822214f0  size 0x28  base C_Node  ctx S_DropOpponentContext
struct S_DropOpponentContext;
class C_DropOpponent : public C_NodeWrapper<C_DropOpponent, C_Node, S_DropOpponentContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DropOpponent;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DropOpponent) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
