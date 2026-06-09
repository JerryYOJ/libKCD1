#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetCurrentPerceptionFocus>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetCurrentPerceptionFocus>  RTTI C_GetCurrentPerceptionFocus  vtable 0x18238c508  size 0x28  base C_Node  ctx S_GetCurrentPerceptionFocusContext
struct S_GetCurrentPerceptionFocusContext;
class C_GetCurrentPerceptionFocus : public C_NodeWrapper<C_GetCurrentPerceptionFocus, C_Node, S_GetCurrentPerceptionFocusContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetCurrentPerceptionFocus;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetCurrentPerceptionFocus) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
