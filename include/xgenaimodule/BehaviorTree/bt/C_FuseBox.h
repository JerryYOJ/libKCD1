#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FuseBox>.

namespace wh::xgenaimodule::BehaviorTree {

// <FuseBox>  RTTI C_FuseBox  vtable 0x18219d8c0  size 0x88  base C_FixedComposite<3>  ctx S_FuseBoxContext
struct S_FuseBoxContext;
class C_FuseBox : public C_NodeWrapper<C_FuseBox, C_FixedComposite<3>, S_FuseBoxContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FuseBox;
    uint8_t _ownState[0x48];   // [UNVERIFIED] own members above C_FixedComposite<3> (0x40)
};
static_assert(sizeof(C_FuseBox) == 0x88);

}  // namespace wh::xgenaimodule::BehaviorTree
