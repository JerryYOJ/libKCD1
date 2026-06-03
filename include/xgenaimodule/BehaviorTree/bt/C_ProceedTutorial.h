#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ProceedTutorial>.

namespace wh::xgenaimodule::BehaviorTree {

// <ProceedTutorial>  RTTI C_ProceedTutorial  vtable 0x182347e90  size 0x28  base C_Node  ctx S_ProceedTutorialContext
struct S_ProceedTutorialContext;
class C_ProceedTutorial : public C_NodeWrapper<C_ProceedTutorial, C_Node, S_ProceedTutorialContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ProceedTutorial) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
