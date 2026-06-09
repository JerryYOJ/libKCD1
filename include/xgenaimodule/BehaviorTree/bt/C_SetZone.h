#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetZone>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetZone>  RTTI C_SetZone  vtable 0x182350938  size 0x28  base C_CombatNode<C_Node>  ctx S_SetZoneContext
struct S_SetZoneContext;
class C_SetZone : public C_NodeWrapper<C_SetZone, C_CombatNode<C_Node>, S_SetZoneContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetZone;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetZone) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
