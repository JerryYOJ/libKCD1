#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HandCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <HandCheck>  RTTI C_HandCheck  vtable 0x1821f5ef8  size 0x28  base C_Node  ctx S_HandCheckContext
struct S_HandCheckContext;
class C_HandCheck : public C_NodeWrapper<C_HandCheck, C_Node, S_HandCheckContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HandCheck;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_HandCheck) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
