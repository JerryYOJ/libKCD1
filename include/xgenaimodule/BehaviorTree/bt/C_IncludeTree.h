#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BehaviorTag.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IncludeTree>.

namespace wh::xgenaimodule::BehaviorTree {

// <IncludeTree>  RTTI C_IncludeTree  vtable 0x1821e8910  size 0x38  base C_BehaviorTag  ctx S_IncludeTreeContext
struct S_IncludeTreeContext;
class C_IncludeTree : public C_NodeWrapper<C_IncludeTree, C_BehaviorTag, S_IncludeTreeContext>
{
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_BehaviorTag (0x28)
};
static_assert(sizeof(C_IncludeTree) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
