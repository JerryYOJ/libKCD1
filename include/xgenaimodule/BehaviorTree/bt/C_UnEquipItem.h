#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <UnEquipItem>.

namespace wh::xgenaimodule::BehaviorTree {

// <UnEquipItem>  RTTI C_UnEquipItem  vtable 0x182216c08  size 0x28  base C_Node  ctx S_UnEquipItemContext
struct S_UnEquipItemContext;
class C_UnEquipItem : public C_NodeWrapper<C_UnEquipItem, C_Node, S_UnEquipItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_UnEquipItem;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_UnEquipItem) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
