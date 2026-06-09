#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RemoveLink>.

namespace wh::xgenaimodule::BehaviorTree {

// <RemoveLink>  RTTI C_RemoveLink  vtable 0x1821fa0e8  size 0x28  base C_Node  ctx S_RemoveLinkContext
struct S_RemoveLinkContext;
class C_RemoveLink : public C_NodeWrapper<C_RemoveLink, C_Node, S_RemoveLinkContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RemoveLink;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RemoveLink) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
