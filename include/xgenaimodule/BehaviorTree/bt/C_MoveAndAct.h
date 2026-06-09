#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_MoveBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MoveAndAct>.

namespace wh::xgenaimodule::BehaviorTree {

// <MoveAndAct>  RTTI C_MoveAndAct  vtable 0x1821d2d20  size 0x38  base C_MoveBase  ctx S_MoveAndActContext
struct S_MoveAndActContext;
class C_MoveAndAct : public C_NodeWrapper<C_MoveAndAct, C_MoveBase, S_MoveAndActContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MoveAndAct;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_MoveBase (0x28)
};
static_assert(sizeof(C_MoveAndAct) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
