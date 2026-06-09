#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkSorterDataSource.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RangeSorter>.

namespace wh::xgenaimodule::BehaviorTree {

// <RangeSorter>  RTTI C_RangeSorter  vtable 0x1821d7f00  size 0x30  base C_LinkSorterDataSource  ctx S_RangeSorterContext
struct S_RangeSorterContext;
class C_RangeSorter : public C_NodeWrapper<C_RangeSorter, C_LinkSorterDataSource, S_RangeSorterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RangeSorter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkSorterDataSource (0x28)
};
static_assert(sizeof(C_RangeSorter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
