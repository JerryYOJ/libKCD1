#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Root>.

namespace wh::xgenaimodule::BehaviorTree {

// <Root>  RTTI C_Root  vtable 0x1821c0160  size 0x60  base C_FixedComposite<2>  ctx S_RootContext
struct S_RootContext;
class C_Root : public C_NodeWrapper<C_Root, C_FixedComposite<2>, S_RootContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Root;
    uint8_t _ownState[0x28];   // [UNVERIFIED] own members above C_FixedComposite<2> (0x38)
};
static_assert(sizeof(C_Root) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
