#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetAngryness>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetAngryness>  RTTI C_GetAngryness  vtable 0x182388bb0  size 0x28  base C_Node  ctx S_GetAngrynessContext
struct S_GetAngrynessContext;
class C_GetAngryness : public C_NodeWrapper<C_GetAngryness, C_Node, S_GetAngrynessContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetAngryness;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetAngryness) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
