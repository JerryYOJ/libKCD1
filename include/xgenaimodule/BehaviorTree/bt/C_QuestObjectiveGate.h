#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <QuestObjectiveGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <QuestObjectiveGate>  RTTI C_QuestObjectiveGate  vtable 0x18220e8b8  size 0x30  base C_PassiveBarrier  ctx S_QuestObjectiveGateContext
struct S_QuestObjectiveGateContext;
class C_QuestObjectiveGate : public C_NodeWrapper<C_QuestObjectiveGate, C_PassiveBarrier, S_QuestObjectiveGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_QuestObjectiveGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_QuestObjectiveGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
