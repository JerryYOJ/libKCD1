#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <QuestObjectiveCondition>.

namespace wh::xgenaimodule::BehaviorTree {

// <QuestObjectiveCondition>  RTTI C_QuestObjectiveCondition  vtable 0x182364cc8  size 0x68  base C_Gate  ctx S_QuestObjectiveCondition
struct S_QuestObjectiveCondition;
class C_QuestObjectiveCondition : public C_NodeWrapper<C_QuestObjectiveCondition, C_Gate, S_QuestObjectiveCondition>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_QuestObjectiveCondition;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_QuestObjectiveCondition) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
