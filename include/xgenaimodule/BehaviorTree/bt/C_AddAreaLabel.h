#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ChangeAreaLabel.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddAreaLabel>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddAreaLabel>  RTTI C_AddAreaLabel  vtable 0x1823938f8  size 0x28  base C_ChangeAreaLabel  ctx S_ChangeAreaLabelContext
struct S_ChangeAreaLabelContext;
class C_AddAreaLabel : public C_NodeWrapper<C_AddAreaLabel, C_ChangeAreaLabel, S_ChangeAreaLabelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AddAreaLabel;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddAreaLabel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
