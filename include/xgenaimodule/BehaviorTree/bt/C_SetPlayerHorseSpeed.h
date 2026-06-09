#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetPlayerHorseSpeed>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetPlayerHorseSpeed>  RTTI C_SetPlayerHorseSpeed  vtable 0x18233af10  size 0x28  base C_Node  ctx S_SetPlayerHorseSpeedContext
struct S_SetPlayerHorseSpeedContext;
class C_SetPlayerHorseSpeed : public C_NodeWrapper<C_SetPlayerHorseSpeed, C_Node, S_SetPlayerHorseSpeedContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetPlayerHorseSpeed;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetPlayerHorseSpeed) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
