#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <UseItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <UseItem>  RTTI C_UseItem  vtable 0x182334568  size 0x28  base C_Node  ctx S_UseItemContext
struct S_UseItemContext;
class C_UseItem : public C_NodeWrapper<C_UseItem, C_Node, S_UseItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_UseItem;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_UseItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
