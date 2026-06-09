#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CancelPerceptionIgnore>.

namespace wh::xgenaimodule::BehaviorTree {

// <CancelPerceptionIgnore>  RTTI C_CancelPerceptionIgnore  vtable 0x18237f0c0  size 0x28  base C_Node  ctx S_CancelPerceptionIgnoreContext
struct S_CancelPerceptionIgnoreContext;
class C_CancelPerceptionIgnore : public C_NodeWrapper<C_CancelPerceptionIgnore, C_Node, S_CancelPerceptionIgnoreContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CancelPerceptionIgnore;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CancelPerceptionIgnore) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
