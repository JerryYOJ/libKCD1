#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ShouldHorseThrowOffAnyone>.

namespace wh::xgenaimodule::BehaviorTree {

// <ShouldHorseThrowOffAnyone>  RTTI C_ShouldHorseThrowOffAnyone  vtable 0x182387218  size 0x30  base C_PassiveBarrier  ctx S_ShouldHorseThrowOffAnyoneContext
struct S_ShouldHorseThrowOffAnyoneContext;
class C_ShouldHorseThrowOffAnyone : public C_NodeWrapper<C_ShouldHorseThrowOffAnyone, C_PassiveBarrier, S_ShouldHorseThrowOffAnyoneContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ShouldHorseThrowOffAnyone) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
