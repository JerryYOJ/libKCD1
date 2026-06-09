#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MoraleCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <MoraleCheck>  RTTI C_MoraleCheck  vtable 0x182387f48  size 0x68  base C_Gate  ctx S_MoraleCheckContext
struct S_MoraleCheckContext;
class C_MoraleCheck : public C_NodeWrapper<C_MoraleCheck, C_Gate, S_MoraleCheckContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MoraleCheck;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_MoraleCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
