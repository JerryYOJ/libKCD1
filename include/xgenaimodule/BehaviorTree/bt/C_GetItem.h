#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetItem>  RTTI C_GetItem  vtable 0x18232a3f0  size 0x28  base C_Node  ctx S_GetItemContext
struct S_GetItemContext;
class C_GetItem : public C_NodeWrapper<C_GetItem, C_Node, S_GetItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetItem;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
