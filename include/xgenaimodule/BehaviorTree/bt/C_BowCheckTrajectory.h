#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BowCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BowCheckTrajectory>.

namespace wh::xgenaimodule::BehaviorTree {

// <BowCheckTrajectory>  RTTI C_BowCheckTrajectory  vtable 0x1823466a0  size 0x28  base C_BowCheckBase  ctx S_BowCheckTrajectoryContext
struct S_BowCheckTrajectoryContext;
class C_BowCheckTrajectory : public C_NodeWrapper<C_BowCheckTrajectory, C_BowCheckBase, S_BowCheckTrajectoryContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BowCheckTrajectory;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_BowCheckTrajectory) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
