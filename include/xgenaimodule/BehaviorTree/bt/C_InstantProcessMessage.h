#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ProcessMessage.h"
#include "C_ProcessMessage.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantProcessMessage>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantProcessMessage>  RTTI C_InstantProcessMessage  vtable 0x18235cc20  size 0x30  base C_ReceiveMessageBase<C_ProcessMessageBase>  ctx S_InstantProcessMessageContext
struct S_InstantProcessMessageContext;
class C_InstantProcessMessage : public C_NodeWrapper<C_InstantProcessMessage, C_ReceiveMessageBase<C_ProcessMessageBase>, S_InstantProcessMessageContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_InstantProcessMessage) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
