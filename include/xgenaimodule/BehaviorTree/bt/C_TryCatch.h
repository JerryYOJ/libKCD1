#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TryCatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <TryCatch>  RTTI C_TryCatch  vtable 0x1821c4258  size 0x60  base C_Composite  ctx S_TryCatchContext
struct S_TryCatchContext;
class C_TryCatch : public C_NodeWrapper<C_TryCatch, C_Composite, S_TryCatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TryCatch;
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_Composite (0x40)
};
static_assert(sizeof(C_TryCatch) == 0x60);

}  // namespace wh::xgenaimodule::BehaviorTree
