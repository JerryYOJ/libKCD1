#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RequestDialog>.

namespace wh::xgenaimodule::BehaviorTree {

// <RequestDialog>  RTTI C_RequestDialog  vtable 0x1822175c8  size 0x28  base C_Node  ctx S_RequestDialogContext
struct S_RequestDialogContext;
class C_RequestDialog : public C_NodeWrapper<C_RequestDialog, C_Node, S_RequestDialogContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RequestDialog) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
