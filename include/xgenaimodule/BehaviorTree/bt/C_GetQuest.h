#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetQuest>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetQuest>  RTTI C_GetQuest  vtable 0x18232c728  size 0x28  base C_Node  ctx S_GetQuestContext
struct S_GetQuestContext;
class C_GetQuest : public C_NodeWrapper<C_GetQuest, C_Node, S_GetQuestContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetQuest;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetQuest) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
