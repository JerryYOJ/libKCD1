#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DestroyInformationCompletely>.

namespace wh::xgenaimodule::BehaviorTree {

// <DestroyInformationCompletely>  RTTI C_DestroyInformationCompletely  vtable 0x1823766f8  size 0x28  base C_Node  ctx S_DestroyInformationCompletelyContext
struct S_DestroyInformationCompletelyContext;
class C_DestroyInformationCompletely : public C_NodeWrapper<C_DestroyInformationCompletely, C_Node, S_DestroyInformationCompletelyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DestroyInformationCompletely;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DestroyInformationCompletely) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
