#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsPointOnNavMesh>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsPointOnNavMesh>  RTTI C_IsPointOnNavMesh  vtable 0x18235d048  size 0x68  base C_Gate  ctx S_IsPointOnNavMeshContext
struct S_IsPointOnNavMeshContext;
class C_IsPointOnNavMesh : public C_NodeWrapper<C_IsPointOnNavMesh, C_Gate, S_IsPointOnNavMeshContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsPointOnNavMesh) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
