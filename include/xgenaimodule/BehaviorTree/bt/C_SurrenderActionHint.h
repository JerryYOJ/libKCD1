#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SurrenderActionHint>.

namespace wh::xgenaimodule::BehaviorTree {

// <SurrenderActionHint>  RTTI C_SurrenderActionHint  vtable 0x18233d6d0  size 0x28  base C_Node  ctx S_SurrenderActionHintContext
struct S_SurrenderActionHintContext;
class C_SurrenderActionHint : public C_NodeWrapper<C_SurrenderActionHint, C_Node, S_SurrenderActionHintContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SurrenderActionHint;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SurrenderActionHint) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
