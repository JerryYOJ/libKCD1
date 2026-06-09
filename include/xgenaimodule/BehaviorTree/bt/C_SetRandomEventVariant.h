#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetRandomEventVariant>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetRandomEventVariant>  RTTI C_SetRandomEventVariant  vtable 0x18234b040  size 0x28  base C_Node  ctx S_RandomEventVariantContext
struct S_RandomEventVariantContext;
class C_SetRandomEventVariant : public C_NodeWrapper<C_SetRandomEventVariant, C_Node, S_RandomEventVariantContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetRandomEventVariant;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetRandomEventVariant) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
