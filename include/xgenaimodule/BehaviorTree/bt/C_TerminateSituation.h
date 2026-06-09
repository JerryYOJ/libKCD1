#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TerminateSituation>.

namespace wh::xgenaimodule::BehaviorTree {

// <TerminateSituation>  RTTI C_TerminateSituation  vtable 0x1823472c8  size 0x28  base C_Node  ctx S_TerminateSituationContext
struct S_TerminateSituationContext;
class C_TerminateSituation : public C_NodeWrapper<C_TerminateSituation, C_Node, S_TerminateSituationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TerminateSituation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TerminateSituation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
