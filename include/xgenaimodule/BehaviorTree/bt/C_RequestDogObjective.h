#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RequestDogObjective>.

namespace wh::xgenaimodule::BehaviorTree {

// <RequestDogObjective>  RTTI C_RequestDogObjective  vtable 0x182325ed8  size 0x28  base C_DefferedStateChange  ctx S_RequestDogObjectiveContext
struct S_RequestDogObjectiveContext;
class C_RequestDogObjective : public C_NodeWrapper<C_RequestDogObjective, C_DefferedStateChange, S_RequestDogObjectiveContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RequestDogObjective;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RequestDogObjective) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
