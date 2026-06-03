#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisableLOD>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisableLOD>  RTTI C_DisableLOD  vtable 0x18235f4e8  size 0x30  base C_DeferredExecution  ctx S_DisableLODContext
struct S_DisableLODContext;
class C_DisableLOD : public C_NodeWrapper<C_DisableLOD, C_DeferredExecution, S_DisableLODContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DisableLOD) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
