#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FormationInSpotsGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <FormationInSpotsGate>  RTTI C_FormationInSpotsGate  vtable 0x18236edc0  size 0x30  base C_ActiveBarrier  ctx S_FormationInSpotsGateContext
struct S_FormationInSpotsGateContext;
class C_FormationInSpotsGate : public C_NodeWrapper<C_FormationInSpotsGate, C_ActiveBarrier, S_FormationInSpotsGateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FormationInSpotsGate;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FormationInSpotsGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
