#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkNoData.h"
#include "../C_Node.h"

// C_LinkSorterDataSource - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_LinkSorterDataSource : public C_LinkNoData<C_Node>   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_LinkSorterDataSource : public C_LinkNoData<C_Node> {};

}  // namespace wh::xgenaimodule::BehaviorTree
