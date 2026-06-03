#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RestrictCamera>.

namespace wh::xgenaimodule::BehaviorTree {

// <RestrictCamera>  RTTI C_RestrictCamera  vtable 0x182364890  size 0x30  base C_WrapperDecorator  ctx S_RestrictCameraContext
struct S_RestrictCameraContext;
class C_RestrictCamera : public C_NodeWrapper<C_RestrictCamera, C_WrapperDecorator, S_RestrictCameraContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_RestrictCamera) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
