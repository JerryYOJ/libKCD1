#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetLevelTransferData>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetLevelTransferData>  RTTI C_GetLevelTransferData  vtable 0x18232d6a8  size 0x28  base C_Node  ctx S_GetLevelTransferDataContext
struct S_GetLevelTransferDataContext;
class C_GetLevelTransferData : public C_NodeWrapper<C_GetLevelTransferData, C_Node, S_GetLevelTransferDataContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetLevelTransferData;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetLevelTransferData) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
