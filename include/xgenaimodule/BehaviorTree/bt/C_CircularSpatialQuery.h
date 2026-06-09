#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CircularSpatialQuery>.

namespace wh::xgenaimodule::BehaviorTree {

// <CircularSpatialQuery>  RTTI C_CircularSpatialQuery  vtable 0x18221dda0  size 0x28  base C_Node  ctx S_CircularSpatialQueryContext
struct S_CircularSpatialQueryContext;
class C_CircularSpatialQuery : public C_NodeWrapper<C_CircularSpatialQuery, C_Node, S_CircularSpatialQueryContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CircularSpatialQuery;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CircularSpatialQuery) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
