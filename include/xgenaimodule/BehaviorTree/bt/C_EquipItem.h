#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EquipItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <EquipItem>  RTTI C_EquipItem  vtable 0x182221eb0  size 0x28  base C_Node  ctx S_EquipItemContext
struct S_EquipItemContext;
class C_EquipItem : public C_NodeWrapper<C_EquipItem, C_Node, S_EquipItemContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_EquipItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
