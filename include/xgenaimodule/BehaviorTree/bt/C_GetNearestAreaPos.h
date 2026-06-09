#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetNearestAreaPos>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetNearestAreaPos>  RTTI C_GetNearestAreaPos  vtable 0x182393080  size 0x28  base C_Node  ctx S_GetNearestAreaPosContext
struct S_GetNearestAreaPosContext;
class C_GetNearestAreaPos : public C_NodeWrapper<C_GetNearestAreaPos, C_Node, S_GetNearestAreaPosContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetNearestAreaPos;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetNearestAreaPos) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
