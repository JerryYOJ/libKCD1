#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RandomItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <RandomItem>  RTTI C_RandomItem  vtable 0x182220b30  size 0x28  base C_Node  ctx S_RandomItemContext
struct S_RandomItemContext;
class C_RandomItem : public C_NodeWrapper<C_RandomItem, C_Node, S_RandomItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RandomItem;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RandomItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
