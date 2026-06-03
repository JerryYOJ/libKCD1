#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <SendMessageToNPC> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <SendMessageToNPC>  RTTI C_SendMessageToNPC  vtable 0x1821e6ba0  size 0x50  base C_InstantSendMessageToNPC
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_SendMessageToNPC : public C_InstantSendMessageToNPC
{
    // [UNVERIFIED] own members; complete object == 0x50
};

}  // namespace wh::xgenaimodule::BehaviorTree
