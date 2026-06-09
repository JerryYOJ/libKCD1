#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

struct S_CombatActorActionAttackParams : public I_CombatActorActionParamsReflect {
    inline static constexpr auto RTTI = Offsets::RTTI_S_CombatActorActionAttackParams;
    ~S_CombatActorActionAttackParams() = default;
    uint64_t m_data;            // +0x08  (init 0)
    uint32_t m_flags;           // +0x10  (init 0x100)
    uint32_t _pad;              // +0x14
};
static_assert(sizeof(S_CombatActorActionAttackParams) == 0x18);

}  // namespace wh::combatmodule
