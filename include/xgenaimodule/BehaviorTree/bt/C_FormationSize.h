#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FormationSize>.

namespace wh::xgenaimodule::BehaviorTree {

// <FormationSize>  RTTI C_FormationSize  vtable 0x18236eab0  size 0x30  base C_ActiveBarrier  ctx S_FormationSizeContext
struct S_FormationSizeContext;
class C_FormationSize : public C_NodeWrapper<C_FormationSize, C_ActiveBarrier, S_FormationSizeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FormationSize) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
