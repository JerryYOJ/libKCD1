#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Block>.

namespace wh::xgenaimodule::BehaviorTree {

// <Block>  RTTI C_Block  vtable 0x18221c5f8  size 0x30  base C_CombatNode<C_Decorator>  ctx S_BlockContext
struct S_BlockContext;
class C_Block : public C_NodeWrapper<C_Block, C_CombatNode<C_Decorator>, S_BlockContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Block;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Block) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
