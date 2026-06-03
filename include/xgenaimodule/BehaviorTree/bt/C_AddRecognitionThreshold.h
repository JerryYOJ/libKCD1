#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddRecognitionThreshold>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddRecognitionThreshold>  RTTI C_AddRecognitionThreshold  vtable 0x18237f188  size 0x30  base C_WrapperDecorator  ctx S_AddRecognitionThresholdContext
struct S_AddRecognitionThresholdContext;
class C_AddRecognitionThreshold : public C_NodeWrapper<C_AddRecognitionThreshold, C_WrapperDecorator, S_AddRecognitionThresholdContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AddRecognitionThreshold) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
