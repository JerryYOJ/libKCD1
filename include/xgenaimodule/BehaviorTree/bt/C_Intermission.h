#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Intermission>.

namespace wh::xgenaimodule::BehaviorTree {

// <Intermission>  RTTI C_Intermission  vtable 0x18236ca50  size 0x28  base C_DefferedStateChange  ctx S_IntermissionContext
struct S_IntermissionContext;
class C_Intermission : public C_NodeWrapper<C_Intermission, C_DefferedStateChange, S_IntermissionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Intermission;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Intermission) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
