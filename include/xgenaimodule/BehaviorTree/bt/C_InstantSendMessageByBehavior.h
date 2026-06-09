#pragma once

#include <cstdint>
#include "SendMessageTower.h"

// BT node <InstantSendMessageByBehavior> (SendMessage MI).

namespace wh::xgenaimodule::BehaviorTree {

// <InstantSendMessageByBehavior>  RTTI C_InstantSendMessageByBehavior  vtable 0x1823926c8  size 0x40  base C_SendToNPC_MultiData
// SendMessage MI/virtual-inheritance family (see bases/SendMessageTower.h).
// ctx None.  Own members [UNVERIFIED]; size is a doc fact
// (virtual-base layout makes a static_assert unreliable here).
class C_InstantSendMessageByBehavior : public C_SendToNPC_MultiData
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantSendMessageByBehavior;
    // [UNVERIFIED] own members; complete object == 0x40
};

}  // namespace wh::xgenaimodule::BehaviorTree
