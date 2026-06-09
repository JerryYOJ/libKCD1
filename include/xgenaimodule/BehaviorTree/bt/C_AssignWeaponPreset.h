#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AssignWeaponPreset>.

namespace wh::xgenaimodule::BehaviorTree {

// <AssignWeaponPreset>  RTTI C_AssignWeaponPreset  vtable 0x18221ecc0  size 0x28  base C_Node  ctx S_AssignWeaponPresetContext
struct S_AssignWeaponPresetContext;
class C_AssignWeaponPreset : public C_NodeWrapper<C_AssignWeaponPreset, C_Node, S_AssignWeaponPresetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AssignWeaponPreset;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AssignWeaponPreset) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
