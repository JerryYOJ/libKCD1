#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CanAssignClothingPresetFromInventory>.

namespace wh::xgenaimodule::BehaviorTree {

// <CanAssignClothingPresetFromInventory>  RTTI C_CanAssignClothingPresetFromInventory  vtable 0x1822129a8  size 0x68  base C_Gate  ctx S_CanAssignClothingPresetFromInventoryContext
struct S_CanAssignClothingPresetFromInventoryContext;
class C_CanAssignClothingPresetFromInventory : public C_NodeWrapper<C_CanAssignClothingPresetFromInventory, C_Gate, S_CanAssignClothingPresetFromInventoryContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_CanAssignClothingPresetFromInventory) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
