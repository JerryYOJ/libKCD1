#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetPredefPathTraverseInfo>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetPredefPathTraverseInfo>  RTTI C_GetPredefPathTraverseInfo  vtable 0x18232c138  size 0x28  base C_Node  ctx S_GetPredefPathTraverseInfoContext
struct S_GetPredefPathTraverseInfoContext;
class C_GetPredefPathTraverseInfo : public C_NodeWrapper<C_GetPredefPathTraverseInfo, C_Node, S_GetPredefPathTraverseInfoContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetPredefPathTraverseInfo) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
