#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetTemporarySuperfaction>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetTemporarySuperfaction>  RTTI C_SetTemporarySuperfaction  vtable 0x18234a3e0  size 0x28  base C_Node  ctx S_SetTemporarySuperfactionContext
struct S_SetTemporarySuperfactionContext;
class C_SetTemporarySuperfaction : public C_NodeWrapper<C_SetTemporarySuperfaction, C_Node, S_SetTemporarySuperfactionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetTemporarySuperfaction) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
