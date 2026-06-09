#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

class C_CombatActionSyncAttackData;

struct S_CombatActorActionSyncAttackParams : public I_CombatActorActionParamsReflect {
    inline static constexpr auto RTTI = Offsets::RTTI_S_CombatActorActionSyncAttackParams;
    ~S_CombatActorActionSyncAttackParams() = default;
    C_CombatActionSyncAttackData* m_pDataRow;  // +0x08  runtime data row (combat_action_sync_attack)
    bool     m_syncFlag;        // +0x10  (init 1)
    uint8_t  _pad[7];           // +0x11
};
static_assert(sizeof(S_CombatActorActionSyncAttackParams) == 0x18);

}  // namespace wh::combatmodule
