#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Observer>.

namespace wh::xgenaimodule::BehaviorTree {

// <Observer>  RTTI C_Observer  vtable 0x1823323e0  size 0x28  base C_Node  ctx S_ObserverContext
struct S_ObserverContext;
class C_Observer : public C_NodeWrapper<C_Observer, C_Node, S_ObserverContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Observer;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Observer) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
