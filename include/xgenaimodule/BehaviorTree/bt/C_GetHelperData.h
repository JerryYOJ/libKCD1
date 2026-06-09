#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetHelperData>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetHelperData>  RTTI C_GetHelperData  vtable 0x182322b00  size 0x28  base C_Node  ctx S_GetHelperDataContext
struct S_GetHelperDataContext;
class C_GetHelperData : public C_NodeWrapper<C_GetHelperData, C_Node, S_GetHelperDataContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetHelperData;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetHelperData) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
