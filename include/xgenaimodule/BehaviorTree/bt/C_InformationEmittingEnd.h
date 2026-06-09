#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InformationEmittingEnd>.

namespace wh::xgenaimodule::BehaviorTree {

// <InformationEmittingEnd>  RTTI C_InformationEmittingEnd  vtable 0x1822247b8  size 0x28  base C_Node  ctx S_InformationEmittingEndContext
struct S_InformationEmittingEndContext;
class C_InformationEmittingEnd : public C_NodeWrapper<C_InformationEmittingEnd, C_Node, S_InformationEmittingEndContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InformationEmittingEnd;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InformationEmittingEnd) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
