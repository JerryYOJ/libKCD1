#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetLastNavmeshPosition>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetLastNavmeshPosition>  RTTI C_GetLastNavmeshPosition  vtable 0x1823223a8  size 0x28  base C_Node  ctx S_GetLastNavmeshPositionContext
struct S_GetLastNavmeshPositionContext;
class C_GetLastNavmeshPosition : public C_NodeWrapper<C_GetLastNavmeshPosition, C_Node, S_GetLastNavmeshPositionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetLastNavmeshPosition;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetLastNavmeshPosition) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
