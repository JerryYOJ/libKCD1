#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <MultiSendMessageToNPC> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <MultiSendMessageToNPC>  RTTI C_MultiSendMessageToNPC  vtable 0x1826ec500  size 0x50  base C_InstantMultiSendMessageToNPC
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_MultiSendMessageToNPC : public C_InstantMultiSendMessageToNPC
{
    // [UNVERIFIED] own members; complete object == 0x50
};

}  // namespace wh::xgenaimodule::BehaviorTree
