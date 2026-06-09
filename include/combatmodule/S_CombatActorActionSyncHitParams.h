#pragma once

#include <cstdint>

namespace wh::combatmodule {

struct C_CombatActionSyncHitData;

struct S_CombatActorActionSyncHitParams {
    C_CombatActionSyncHitData* m_pDataRow;  // +0x00  runtime data row (combat_action_sync_hit)
};
static_assert(sizeof(S_CombatActorActionSyncHitParams) == 0x08);

}  // namespace wh::combatmodule
