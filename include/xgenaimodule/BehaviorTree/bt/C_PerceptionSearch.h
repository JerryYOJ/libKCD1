#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PerceptionSearch>.

namespace wh::xgenaimodule::BehaviorTree {

// <PerceptionSearch>  RTTI C_PerceptionSearch  vtable 0x18238cf08  size 0x68  base C_FixedComposite<2>  ctx S_PerceptionSearchContext
struct S_PerceptionSearchContext;
class C_PerceptionSearch : public C_NodeWrapper<C_PerceptionSearch, C_FixedComposite<2>, S_PerceptionSearchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PerceptionSearch;
    uint8_t _ownState[0x30];   // [UNVERIFIED] own members above C_FixedComposite<2> (0x38)
};
static_assert(sizeof(C_PerceptionSearch) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
