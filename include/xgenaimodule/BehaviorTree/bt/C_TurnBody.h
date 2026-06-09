#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TurnBody>.

namespace wh::xgenaimodule::BehaviorTree {

// <TurnBody>  RTTI C_TurnBody  vtable ?  size 0x28  base C_Node  ctx S_TurnBodyContext
struct S_TurnBodyContext;
class C_TurnBody : public C_NodeWrapper<C_TurnBody, C_Node, S_TurnBodyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TurnBody;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TurnBody) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
