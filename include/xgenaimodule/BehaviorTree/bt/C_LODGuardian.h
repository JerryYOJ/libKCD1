#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LODGuardian>.

namespace wh::xgenaimodule::BehaviorTree {

// <LODGuardian>  RTTI C_LODGuardian  vtable 0x18219e2b0  size 0x58  base C_FixedComposite<2>  ctx S_LODGuardianContext
struct S_LODGuardianContext;
class C_LODGuardian : public C_NodeWrapper<C_LODGuardian, C_FixedComposite<2>, S_LODGuardianContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LODGuardian;
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_FixedComposite<2> (0x38)
};
static_assert(sizeof(C_LODGuardian) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
