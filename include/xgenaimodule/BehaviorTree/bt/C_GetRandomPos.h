#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetRandomPos>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetRandomPos>  RTTI C_GetRandomPos  vtable 0x18232c3a8  size 0x28  base C_Node  ctx S_GetRandomPosContext
struct S_GetRandomPosContext;
class C_GetRandomPos : public C_NodeWrapper<C_GetRandomPos, C_Node, S_GetRandomPosContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetRandomPos;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetRandomPos) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
