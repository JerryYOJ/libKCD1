#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearInbox>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearInbox>  RTTI C_ClearInbox  vtable 0x1821fadc0  size 0x28  base C_Node  ctx S_ClearInboxContext
struct S_ClearInboxContext;
class C_ClearInbox : public C_NodeWrapper<C_ClearInbox, C_Node, S_ClearInboxContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ClearInbox;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearInbox) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
