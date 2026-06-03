#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AttachObject>.

namespace wh::xgenaimodule::BehaviorTree {

// <AttachObject>  RTTI C_AttachObject  vtable 0x18231d7e8  size 0x28  base C_Node  ctx S_AttachObjectContext
struct S_AttachObjectContext;
class C_AttachObject : public C_NodeWrapper<C_AttachObject, C_Node, S_AttachObjectContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AttachObject) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
