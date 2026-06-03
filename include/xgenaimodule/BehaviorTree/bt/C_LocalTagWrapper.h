#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LocalTagWrapper>.

namespace wh::xgenaimodule::BehaviorTree {

// <LocalTagWrapper>  RTTI C_LocalTagWrapper  vtable 0x182366510  size 0x30  base C_ForwardingData<C_WrapperDecorator>  ctx S_LocalTagWrapperContext
struct S_LocalTagWrapperContext;
class C_LocalTagWrapper : public C_NodeWrapper<C_LocalTagWrapper, C_ForwardingData<C_WrapperDecorator>, S_LocalTagWrapperContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LocalTagWrapper) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
