#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetCompanion>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetCompanion>  RTTI C_SetCompanion  vtable 0x182325e10  size 0x28  base C_Node  ctx S_SetCompanionContext
struct S_SetCompanionContext;
class C_SetCompanion : public C_NodeWrapper<C_SetCompanion, C_Node, S_SetCompanionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetCompanion;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetCompanion) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
