#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_Root.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LambdaRoot>.

namespace wh::xgenaimodule::BehaviorTree {

// <LambdaRoot>  RTTI C_LambdaRoot  vtable 0x1821bfc08  size 0x60  base C_Root  ctx S_RootContext
struct S_RootContext;
class C_LambdaRoot : public C_NodeWrapper<C_LambdaRoot, C_Root, S_RootContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LambdaRoot;
    // no own data members (object == 0x60)
};
static_assert(sizeof(C_LambdaRoot) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
