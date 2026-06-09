#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

struct S_CombatActorActionSyncAttackParams : public I_CombatActorActionParamsReflect {
    inline static constexpr auto RTTI = Offsets::RTTI_S_CombatActorActionSyncAttackParams;
    ~S_CombatActorActionSyncAttackParams() = default;
    uint64_t m_data;            // +0x08  (init 0)
    bool     m_syncFlag;        // +0x10  (init 1)
    uint8_t  _pad[7];           // +0x11
};
static_assert(sizeof(S_CombatActorActionSyncAttackParams) == 0x18);

}  // namespace wh::combatmodule
