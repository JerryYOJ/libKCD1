#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkSorterDataSource.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SleepQualitySorter>.

namespace wh::xgenaimodule::BehaviorTree {

// <SleepQualitySorter>  RTTI C_SleepQualitySorter  vtable 0x182700b78  size 0x30  base C_LinkSorterDataSource  ctx S_SleepQualitySorterContext
struct S_SleepQualitySorterContext;
class C_SleepQualitySorter : public C_NodeWrapper<C_SleepQualitySorter, C_LinkSorterDataSource, S_SleepQualitySorterContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkSorterDataSource (0x28)
};
static_assert(sizeof(C_SleepQualitySorter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
