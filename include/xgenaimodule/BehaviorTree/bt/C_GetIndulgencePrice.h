#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetIndulgencePrice>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetIndulgencePrice>  RTTI C_GetIndulgencePrice  vtable 0x18233be70  size 0x28  base C_Node  ctx S_GetIndulgencePriceContext
struct S_GetIndulgencePriceContext;
class C_GetIndulgencePrice : public C_NodeWrapper<C_GetIndulgencePrice, C_Node, S_GetIndulgencePriceContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetIndulgencePrice;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetIndulgencePrice) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
