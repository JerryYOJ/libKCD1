#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AlignmentWrapper>.

namespace wh::xgenaimodule::BehaviorTree {

// <AlignmentWrapper>  RTTI C_AlignmentWrapper  vtable 0x182357168  size 0x30  base C_ForwardingData<C_WrapperDecorator>  ctx S_AlignmentWrapperContext
struct S_AlignmentWrapperContext;
class C_AlignmentWrapper : public C_NodeWrapper<C_AlignmentWrapper, C_ForwardingData<C_WrapperDecorator>, S_AlignmentWrapperContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AlignmentWrapper;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AlignmentWrapper) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
