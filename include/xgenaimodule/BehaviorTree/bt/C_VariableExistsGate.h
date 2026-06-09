#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <VariableExistsGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <VariableExistsGate>  RTTI C_VariableExistsGate  vtable 0x18219f1b0  size 0x68  base C_Gate  ctx S_VariableExistsGateContext
struct S_VariableExistsGateContext;
class C_VariableExistsGate : public C_NodeWrapper<C_VariableExistsGate, C_Gate, S_VariableExistsGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_VariableExistsGate;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_VariableExistsGate) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
