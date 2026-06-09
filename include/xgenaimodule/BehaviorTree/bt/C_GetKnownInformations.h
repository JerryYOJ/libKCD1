#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetKnownInformations>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetKnownInformations>  RTTI C_GetKnownInformations  vtable 0x182374e10  size 0x28  base C_Node  ctx S_GetKnownInformationsContext
struct S_GetKnownInformationsContext;
class C_GetKnownInformations : public C_NodeWrapper<C_GetKnownInformations, C_Node, S_GetKnownInformationsContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetKnownInformations;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetKnownInformations) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
