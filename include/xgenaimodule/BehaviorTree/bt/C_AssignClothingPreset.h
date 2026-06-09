#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AssignClothingPreset>.

namespace wh::xgenaimodule::BehaviorTree {

// <AssignClothingPreset>  RTTI C_AssignClothingPreset  vtable 0x18221f1a0  size 0x28  base C_Node  ctx S_AssignClothingPresetContext
struct S_AssignClothingPresetContext;
class C_AssignClothingPreset : public C_NodeWrapper<C_AssignClothingPreset, C_Node, S_AssignClothingPresetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AssignClothingPreset;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AssignClothingPreset) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
