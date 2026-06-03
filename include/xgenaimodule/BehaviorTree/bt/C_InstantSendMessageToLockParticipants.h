#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <InstantSendMessageToLockParticipants> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <InstantSendMessageToLockParticipants>  RTTI C_InstantSendMessageToLockParticipants  vtable 0x18233a9f8  size 0x48  base C_SendToNPC_MultiData
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_InstantSendMessageToLockParticipants : public C_SendToNPC_MultiData
{
    // [UNVERIFIED] own members; complete object == 0x48
};

}  // namespace wh::xgenaimodule::BehaviorTree
