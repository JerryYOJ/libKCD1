#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LuaGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <LuaGate>  RTTI C_LuaGate  vtable 0x1821a0838  size 0x78  base C_Gate  ctx S_LuaGateContext
struct S_LuaGateContext;
class C_LuaGate : public C_NodeWrapper<C_LuaGate, C_Gate, S_LuaGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LuaGate;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_Gate (0x68)
};
static_assert(sizeof(C_LuaGate) == 0x78);

}  // namespace wh::xgenaimodule::BehaviorTree
