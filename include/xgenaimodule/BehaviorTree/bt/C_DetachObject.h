#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DetachObject>.

namespace wh::xgenaimodule::BehaviorTree {

// <DetachObject>  RTTI C_DetachObject  vtable 0x1823254b8  size 0x28  base C_Node  ctx S_DetachObjectContext
struct S_DetachObjectContext;
class C_DetachObject : public C_NodeWrapper<C_DetachObject, C_Node, S_DetachObjectContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DetachObject;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DetachObject) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
