#pragma once

#include <cstdint>
#include "C_InstantSendMessageToNPC.h"   // hand-RE'd: C_SendMessageBase, C_SendToNPC_Data, C_InstantSendMessageToNPC

// ===========================================================================
// SendMessageTower.h  -  remaining KCD BT "send message to NPC" base classes.
//
// HAND-AUTHORED from verified RTTI (workflow whtqaju6j; CHD/COL reads, high conf;
// see analysis/bt_mi_node_rtti_verified.json). The base classes C_SendMessageBase,
// C_SendToNPC_Data and C_InstantSendMessageToNPC are owned by the hand-RE'd
// ../C_InstantSendMessageToNPC.h (included above); this header adds ONLY the
// remaining tower classes used by the multi/time/behavior send-message leaves.
//
// VERIFIED STRUCTURE (CHD attr=3 = MI|VI; the diamond collapses onto the single
// shared `virtual C_SendMessageBase`):
//   C_SendToNPC_MultiData          : virtual C_SendMessageBase            size 0x38
//   C_InstantMultiSendMessageToNPC : C_SendToNPC_MultiData                size 0x40
//   C_SendToNPC_TimeBase           : virtual C_SendMessageBase            [abstract]
//   C_MultiSendToNPC_Time          : C_SendToNPC_TimeBase,
//                                    virtual C_SendToNPC_MultiData         size 0x48
//
// Own members [UNVERIFIED] (raw padding to documented size); virtual-base layout
// makes sizeof subtle, so leaf node headers record size as a doc fact (no assert).
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

class C_SendToNPC_MultiData : public virtual C_SendMessageBase {
    uint8_t _ownState[0x08];   // [UNVERIFIED]; complete object 0x38
};

class C_InstantMultiSendMessageToNPC : public C_SendToNPC_MultiData {
    // complete object 0x40 [own members UNVERIFIED]
};

class C_SendToNPC_TimeBase : public virtual C_SendMessageBase {
    // abstract / never most-derived; standalone size [UNVERIFIED]
};

// Apex: genuine MI — primary non-virtual C_SendToNPC_TimeBase + virtual
// C_SendToNPC_MultiData, diamond collapsing onto the shared virtual C_SendMessageBase.
class C_MultiSendToNPC_Time
    : public C_SendToNPC_TimeBase
    , public virtual C_SendToNPC_MultiData {
    // complete object 0x48 [own members UNVERIFIED]
};

}  // namespace wh::xgenaimodule::BehaviorTree
