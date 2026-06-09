#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Jail>.

namespace wh::xgenaimodule::BehaviorTree {

// <Jail>  RTTI C_Jail  vtable 0x18233ecc8  size 0x28  base C_Node  ctx S_JailContext
struct S_JailContext;
class C_Jail : public C_NodeWrapper<C_Jail, C_Node, S_JailContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Jail;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Jail) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
