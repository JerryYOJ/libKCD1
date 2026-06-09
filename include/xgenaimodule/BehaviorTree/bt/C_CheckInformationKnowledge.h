#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CheckInformationKnowledge>.

namespace wh::xgenaimodule::BehaviorTree {

// <CheckInformationKnowledge>  RTTI C_CheckInformationKnowledge  vtable 0x182376320  size 0x28  base C_Node  ctx S_CheckInformationKnowledgeContext
struct S_CheckInformationKnowledgeContext;
class C_CheckInformationKnowledge : public C_NodeWrapper<C_CheckInformationKnowledge, C_Node, S_CheckInformationKnowledgeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CheckInformationKnowledge;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CheckInformationKnowledge) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
