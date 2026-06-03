#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ForEach>.

namespace wh::xgenaimodule::BehaviorTree {

// <ForEach>  RTTI C_ForEach  vtable 0x1821e7978  size 0x30  base C_ForBase  ctx S_ForEachContext
struct S_ForEachContext;
class C_ForEach : public C_NodeWrapper<C_ForEach, C_ForBase, S_ForEachContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ForEach) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
