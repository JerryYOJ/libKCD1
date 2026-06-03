#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <For>.

namespace wh::xgenaimodule::BehaviorTree {

// <For>  RTTI C_For  vtable 0x1821e7e88  size 0x30  base C_ForBase  ctx S_ForContext
struct S_ForContext;
class C_For : public C_NodeWrapper<C_For, C_ForBase, S_ForContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_For) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
