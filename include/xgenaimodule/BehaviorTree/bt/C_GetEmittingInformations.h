#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetEmittingInformations>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetEmittingInformations>  RTTI C_GetEmittingInformations  vtable 0x1823757d8  size 0x28  base C_Node  ctx S_GetEmittingInformationsContext
struct S_GetEmittingInformationsContext;
class C_GetEmittingInformations : public C_NodeWrapper<C_GetEmittingInformations, C_Node, S_GetEmittingInformationsContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetEmittingInformations;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetEmittingInformations) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
