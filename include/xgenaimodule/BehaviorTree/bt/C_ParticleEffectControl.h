#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ParticleEffectControl>.

namespace wh::xgenaimodule::BehaviorTree {

// <ParticleEffectControl>  RTTI C_ParticleEffectControl  vtable 0x1823320e0  size 0x28  base C_Node  ctx S_ParticleEffectControlContext
struct S_ParticleEffectControlContext;
class C_ParticleEffectControl : public C_NodeWrapper<C_ParticleEffectControl, C_Node, S_ParticleEffectControlContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ParticleEffectControl;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ParticleEffectControl) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
