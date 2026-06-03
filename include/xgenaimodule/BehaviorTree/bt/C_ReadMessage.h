#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ProcessMessage.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ReadMessage>.

namespace wh::xgenaimodule::BehaviorTree {

// <ReadMessage>  RTTI C_ReadMessage  vtable 0x1821ea848  size 0x28  base C_ReceiveMessageTimed<C_Node>  ctx S_BaseNodeContext
class C_ReadMessage : public C_NodeWrapper<C_ReadMessage, C_ReceiveMessageTimed<C_Node>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ReadMessage) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
