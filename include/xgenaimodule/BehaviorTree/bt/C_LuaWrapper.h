#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LuaWrapper>.

namespace wh::xgenaimodule::BehaviorTree {

// <LuaWrapper>  RTTI C_LuaWrapper  vtable 0x1821a0cf0  size 0x60  base C_Decorator  ctx S_LuaWrapperContext
struct S_LuaWrapperContext;
class C_LuaWrapper : public C_NodeWrapper<C_LuaWrapper, C_Decorator, S_LuaWrapperContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LuaWrapper;
    uint8_t _ownState[0x30];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_LuaWrapper) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
