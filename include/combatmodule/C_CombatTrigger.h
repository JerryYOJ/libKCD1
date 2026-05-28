#pragma once

#include <cstdint>
#include "C_CombatActorUpdatedObject.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatTrigger — base class for all combat timing triggers.
//
// RTTI: .?AVC_CombatTrigger@combatmodule@wh@@
// vtable @ 0x1821BEEF8 (12 slots: [0]-[11])
// Inherits: C_CombatActorUpdatedObject : C_CombatActorObject
//
// Inherited slots [0]-[7]:
//   [0] dtor, [1] unk_1, [2] GetSubsystemId, [3] GetName,
//   [4] GetDebugLabel, [5] GetDebugInfo, [6] unk_6, [7] Update
//
// New slots [8]-[11]:
//   [8]  nop
//   [9]  nop
//   [10] nop
//   [11] purecall
// ---------------------------------------------------------------------------
class C_CombatTrigger : public C_CombatActorUpdatedObject {
public:
    ~C_CombatTrigger() override = default;          // [0]  sub_180FAA03C
    virtual void unk_8() {}                         // [8]  nop
    virtual void unk_9() {}                         // [9]  nop
    virtual void unk_10() {}                        // [10] nop
    virtual void unk_11() = 0;                      // [11] purecall
};

}  // namespace wh::combatmodule
