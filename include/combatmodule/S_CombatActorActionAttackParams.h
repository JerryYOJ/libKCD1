#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

class C_CombatActionAttackData;  // the selected candidate this params forwards reads into

// S_CombatActorActionAttackParams -- the polymorphic params the attack action embeds at
// +0xD0 (C_ParamAction::m_params). Its base reflection vtable's getters all dereference
// m_pAttackData: slot[1] -> cand+0xD8, slot[10] -> cand+0xE0, slot[11] -> cand+0xE8
// (m_executedZone). Swapping m_pAttackData re-points every one of those getters coherently.
struct S_CombatActorActionAttackParams : public I_CombatActorActionParamsReflect {
    inline static constexpr auto RTTI = Offsets::RTTI_S_CombatActorActionAttackParams;
    ~S_CombatActorActionAttackParams() = default;
    C_CombatActionAttackData* m_pAttackData;  // +0x08  selected candidate (init 0) = action+0xD8
    uint32_t                  m_flags;         // +0x10  (init 0x100)
    uint32_t                  _pad;            // +0x14
};
static_assert(sizeof(S_CombatActorActionAttackParams) == 0x18);

}  // namespace wh::combatmodule
