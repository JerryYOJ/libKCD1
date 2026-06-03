#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BuffDecoratorBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DecoratorBuff>.

namespace wh::xgenaimodule::BehaviorTree {

// <DecoratorBuff>  RTTI C_DecoratorBuff  vtable 0x1821ed138  size 0x30  base C_BuffDecoratorBase  ctx S_DecoratorBuffContext
struct S_DecoratorBuffContext;
class C_DecoratorBuff : public C_NodeWrapper<C_DecoratorBuff, C_BuffDecoratorBase, S_DecoratorBuffContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DecoratorBuff) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
