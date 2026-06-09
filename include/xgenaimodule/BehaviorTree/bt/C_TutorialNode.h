#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TutorialNode>.

namespace wh::xgenaimodule::BehaviorTree {

// <TutorialNode>  RTTI C_TutorialNode  vtable 0x182348100  size 0x28  base C_Node  ctx S_TutorialNodeContext
struct S_TutorialNodeContext;
class C_TutorialNode : public C_NodeWrapper<C_TutorialNode, C_Node, S_TutorialNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TutorialNode;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TutorialNode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
