#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetHerbsInArea>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetHerbsInArea>  RTTI C_GetHerbsInArea  vtable 0x182322e00  size 0x28  base C_Node  ctx S_GetHerbsInAreaContext
struct S_GetHerbsInAreaContext;
class C_GetHerbsInArea : public C_NodeWrapper<C_GetHerbsInArea, C_Node, S_GetHerbsInAreaContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetHerbsInArea;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetHerbsInArea) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
