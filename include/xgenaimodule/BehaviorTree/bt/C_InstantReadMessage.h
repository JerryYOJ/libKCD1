#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ProcessMessage.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantReadMessage>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantReadMessage>  RTTI C_InstantReadMessage  vtable 0x1821ea368  size 0x28  base C_ReceiveMessageBase<C_Node>  ctx S_BaseNodeContext
class C_InstantReadMessage : public C_NodeWrapper<C_InstantReadMessage, C_ReceiveMessageBase<C_Node>, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantReadMessage;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantReadMessage) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
