#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetItemProperty>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetItemProperty>  RTTI C_SetItemProperty  vtable 0x1821f34f0  size 0x28  base C_Node  ctx S_SetItemPropertyContext
struct S_SetItemPropertyContext;
class C_SetItemProperty : public C_NodeWrapper<C_SetItemProperty, C_Node, S_SetItemPropertyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetItemProperty;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetItemProperty) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
