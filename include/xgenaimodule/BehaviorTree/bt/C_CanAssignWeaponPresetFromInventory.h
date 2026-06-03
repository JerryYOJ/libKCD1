#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CanAssignWeaponPresetFromInventory>.

namespace wh::xgenaimodule::BehaviorTree {

// <CanAssignWeaponPresetFromInventory>  RTTI C_CanAssignWeaponPresetFromInventory  vtable 0x18232ad10  size 0x68  base C_Gate  ctx S_CanAssignWeaponPresetFromInventoryContext
struct S_CanAssignWeaponPresetFromInventoryContext;
class C_CanAssignWeaponPresetFromInventory : public C_NodeWrapper<C_CanAssignWeaponPresetFromInventory, C_Gate, S_CanAssignWeaponPresetFromInventoryContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_CanAssignWeaponPresetFromInventory) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
