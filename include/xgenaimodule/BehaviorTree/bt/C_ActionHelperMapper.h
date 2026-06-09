#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ActionHelperMapper>.

namespace wh::xgenaimodule::BehaviorTree {

// <ActionHelperMapper>  RTTI C_ActionHelperMapper  vtable 0x18221b520  size 0x28  base C_Node  ctx S_ActionHelperMapperContext
struct S_ActionHelperMapperContext;
class C_ActionHelperMapper : public C_NodeWrapper<C_ActionHelperMapper, C_Node, S_ActionHelperMapperContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ActionHelperMapper;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ActionHelperMapper) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
