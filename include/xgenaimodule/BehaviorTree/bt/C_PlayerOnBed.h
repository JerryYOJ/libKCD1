#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerOnBed>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerOnBed>  RTTI C_PlayerOnBed  vtable 0x18233e550  size 0x30  base C_Decorator  ctx S_PlayerOnBedContext
struct S_PlayerOnBedContext;
class C_PlayerOnBed : public C_NodeWrapper<C_PlayerOnBed, C_Decorator, S_PlayerOnBedContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayerOnBed;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_PlayerOnBed) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
