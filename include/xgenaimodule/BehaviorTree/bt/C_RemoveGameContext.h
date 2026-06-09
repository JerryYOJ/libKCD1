#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RemoveGameContext>.

namespace wh::xgenaimodule::BehaviorTree {

// <RemoveGameContext>  RTTI C_RemoveGameContext  vtable 0x182323df8  size 0x28  base C_Node  ctx S_GameContext
struct S_GameContext;
class C_RemoveGameContext : public C_NodeWrapper<C_RemoveGameContext, C_Node, S_GameContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RemoveGameContext;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RemoveGameContext) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
