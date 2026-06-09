#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ChangeAreaLabel.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RemoveAreaLabel>.

namespace wh::xgenaimodule::BehaviorTree {

// <RemoveAreaLabel>  RTTI C_RemoveAreaLabel  vtable 0x1823932f0  size 0x28  base C_ChangeAreaLabel  ctx S_ChangeAreaLabelContext
struct S_ChangeAreaLabelContext;
class C_RemoveAreaLabel : public C_NodeWrapper<C_RemoveAreaLabel, C_ChangeAreaLabel, S_ChangeAreaLabelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RemoveAreaLabel;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RemoveAreaLabel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
