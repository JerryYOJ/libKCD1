#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <SendMessageToInhabitants> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <SendMessageToInhabitants>  RTTI C_SendMessageToInhabitants  vtable 0x182702888  size 0x58  base C_MultiSendToNPC_Time
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_SendMessageToInhabitants : public C_MultiSendToNPC_Time
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SendMessageToInhabitants;
    // [UNVERIFIED] own members; complete object == 0x58
};

}  // namespace wh::xgenaimodule::BehaviorTree
