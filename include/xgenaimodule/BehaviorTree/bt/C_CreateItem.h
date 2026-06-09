#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CreateItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <CreateItem>  RTTI C_CreateItem  vtable 0x1821ff370  size 0x28  base C_Node  ctx S_CreateItemContext
struct S_CreateItemContext;
class C_CreateItem : public C_NodeWrapper<C_CreateItem, C_Node, S_CreateItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CreateItem;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CreateItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
