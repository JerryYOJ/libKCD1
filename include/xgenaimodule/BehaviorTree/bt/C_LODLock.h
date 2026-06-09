#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LODLock>.

namespace wh::xgenaimodule::BehaviorTree {

// <LODLock>  RTTI C_LODLock  vtable 0x1821ecc28  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_LODLock : public C_NodeWrapper<C_LODLock, C_WrapperDecorator, S_WrapperDecoratorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LODLock;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LODLock) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
