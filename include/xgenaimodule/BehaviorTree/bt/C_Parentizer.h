#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Parentizer>.

namespace wh::xgenaimodule::BehaviorTree {

// <Parentizer>  RTTI C_Parentizer  vtable 0x182380bf0  size 0x28  base C_Node  ctx S_ParentizerContext
struct S_ParentizerContext;
class C_Parentizer : public C_NodeWrapper<C_Parentizer, C_Node, S_ParentizerContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Parentizer;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Parentizer) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
