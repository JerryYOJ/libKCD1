#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <SendMessageByBehavior> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <SendMessageByBehavior>  RTTI C_SendMessageByBehavior  vtable 0x182702618  size 0x50  base C_MultiSendToNPC_Time
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_SendMessageByBehavior : public C_MultiSendToNPC_Time
{
    // [UNVERIFIED] own members; complete object == 0x50
};

}  // namespace wh::xgenaimodule::BehaviorTree
