#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DismissSearchCandidate>.

namespace wh::xgenaimodule::BehaviorTree {

// <DismissSearchCandidate>  RTTI C_DismissSearchCandidate  vtable 0x18237f648  size 0x28  base C_Node  ctx S_DismissSearchCandidateContext
struct S_DismissSearchCandidateContext;
class C_DismissSearchCandidate : public C_NodeWrapper<C_DismissSearchCandidate, C_Node, S_DismissSearchCandidateContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DismissSearchCandidate) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
