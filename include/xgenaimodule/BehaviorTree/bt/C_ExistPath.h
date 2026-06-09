#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearch.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ExistPath>.

namespace wh::xgenaimodule::BehaviorTree {

// <ExistPath>  RTTI C_ExistPath  vtable 0x1821d5d58  size 0x60  base C_GraphSearch  ctx S_ExistPathContext
struct S_ExistPathContext;
class C_ExistPath : public C_NodeWrapper<C_ExistPath, C_GraphSearch, S_ExistPathContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ExistPath;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearch (0x58)
};
static_assert(sizeof(C_ExistPath) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
