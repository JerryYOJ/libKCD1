#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetVariable>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetVariable>  RTTI C_SetVariable  vtable 0x1821a1208  size 0x38  base C_Node  ctx S_SetVariableContext
struct S_SetVariableContext;
class C_SetVariable : public C_NodeWrapper<C_SetVariable, C_Node, S_SetVariableContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetVariable;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_Node (0x28)
};
static_assert(sizeof(C_SetVariable) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
