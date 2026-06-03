#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasActiveQuestMarker>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasActiveQuestMarker>  RTTI C_HasActiveQuestMarker  vtable 0x18235e7b8  size 0x68  base C_Gate  ctx S_HasActiveQuestMarkerContext
struct S_HasActiveQuestMarkerContext;
class C_HasActiveQuestMarker : public C_NodeWrapper<C_HasActiveQuestMarker, C_Gate, S_HasActiveQuestMarkerContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasActiveQuestMarker) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
