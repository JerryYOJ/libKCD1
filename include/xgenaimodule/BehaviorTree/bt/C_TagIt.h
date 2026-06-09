#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TagIt>.

namespace wh::xgenaimodule::BehaviorTree {

// <TagIt>  RTTI C_TagIt  vtable 0x18220f988  size 0x30  base C_Decorator  ctx S_TagItContext
struct S_TagItContext;
class C_TagIt : public C_NodeWrapper<C_TagIt, C_Decorator, S_TagItContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TagIt;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_TagIt) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
