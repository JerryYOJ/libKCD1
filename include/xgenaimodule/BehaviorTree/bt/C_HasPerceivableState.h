#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasPerceivableState>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasPerceivableState>  RTTI C_HasPerceivableState  vtable 0x18221fc00  size 0x68  base C_Gate  ctx S_HasPerceivableStateContext
struct S_HasPerceivableStateContext;
class C_HasPerceivableState : public C_NodeWrapper<C_HasPerceivableState, C_Gate, S_HasPerceivableStateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HasPerceivableState;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasPerceivableState) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
