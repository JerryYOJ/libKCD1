#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CallBehavior.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CallBehaviorPatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <CallBehaviorPatch>  RTTI C_CallBehaviorPatch  vtable 0x1826eed48  size 0x38  base C_CallBehavior  ctx S_CallBehaviorPatchContext
struct S_CallBehaviorPatchContext;
class C_CallBehaviorPatch : public C_NodeWrapper<C_CallBehaviorPatch, C_CallBehavior, S_CallBehaviorPatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CallBehaviorPatch;
    // no own data members (object == 0x38)
};
static_assert(sizeof(C_CallBehaviorPatch) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
