#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DoDialog>.

namespace wh::xgenaimodule::BehaviorTree {

// <DoDialog>  RTTI C_DoDialog  vtable 0x182217b28  size 0x28  base C_DefferedStateChange  ctx S_DoDialogContext
struct S_DoDialogContext;
class C_DoDialog : public C_NodeWrapper<C_DoDialog, C_DefferedStateChange, S_DoDialogContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DoDialog;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DoDialog) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
