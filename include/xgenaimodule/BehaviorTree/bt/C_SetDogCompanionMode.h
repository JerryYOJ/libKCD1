#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetDogCompanionMode>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetDogCompanionMode>  RTTI C_SetDogCompanionMode  vtable 0x182325848  size 0x28  base C_Node  ctx S_SetDogCompanionModeContext
struct S_SetDogCompanionModeContext;
class C_SetDogCompanionMode : public C_NodeWrapper<C_SetDogCompanionMode, C_Node, S_SetDogCompanionModeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetDogCompanionMode;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetDogCompanionMode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
