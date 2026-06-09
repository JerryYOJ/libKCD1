#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ReadinessWait>.

namespace wh::xgenaimodule::BehaviorTree {

// <ReadinessWait>  RTTI C_ReadinessWait  vtable 0x1826ecc40  size 0x30  base C_Node  ctx S_ReadinessWaitContext
struct S_ReadinessWaitContext;
class C_ReadinessWait : public C_NodeWrapper<C_ReadinessWait, C_Node, S_ReadinessWaitContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ReadinessWait;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_Node (0x28)
};
static_assert(sizeof(C_ReadinessWait) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
