#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetVisibility>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetVisibility>  RTTI C_SetVisibility  vtable 0x182349de0  size 0x28  base C_Node  ctx S_SetVisibilityContext
struct S_SetVisibilityContext;
class C_SetVisibility : public C_NodeWrapper<C_SetVisibility, C_Node, S_SetVisibilityContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetVisibility;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetVisibility) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
