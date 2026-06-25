#pragma once

#include <cstdint>
#include "C_CombatActorUpdatedObject.h"  // base (-> C_CombatActorObject, E_CombatSubsystem)
#include "I_CombatActorAction.h"         // I_CombatActorActionPtr (= _smart_ptr<I_CombatActorAction>)

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActorOpponentManager — per-actor combat subsystem that tracks the
// owner's current melee opponent / target and mediates the "exclusive lock"
// handshake between two fighting actors.
//
// RTTI: .?AVC_CombatActorOpponentManager@combatmodule@wh@@
// vtable @ 0x182227560
// Constructor: sub_1805FD660(this, owner)   (GetName() == "OpponentManager")
// Size: 0x40 bytes.  Lives on C_CombatActor at +0x730 (m_pOpponentManager).
//
// Inheritance (from ctor sub_1805FD660 -> base ctor sub_180431218(this,owner,4)):
//   C_CombatActorOpponentManager
//     C_CombatActorUpdatedObject   (adds Update tick; m_updateFlag @ +0x10)
//       C_CombatActorObject        (m_pOwner @ +0x08)
//
// The owner's current target lives in S_CombatActorState (m_pPrevTarget +0xC98,
// m_pCurrentTarget +0xCA0, m_pOpponent +0xCA8). When the engine changes the
// current target, OnTargetChange() fires, CheckOpponent() gates it, and
// UpdateOpponent() commits the new opponent: it releases the prior opponent's
// exclusive lock and calls C_CombatActor::LinkTarget (sub_1805FB560) to wire up
// the opponent->self signal relays (m_onOpponentGuardType2, m_onOpponentHandSlot,
// m_onOpponentActionChanged, ... documented in C_CombatActor.h).
//
// vtable layout (base C_CombatActorObject portion is interfuscator-shuffled; the
// two manager-specific slots [8]/[9] are appended in declaration order):
//   [0] ~dtor          override
//   [1] Reset          override   sub_180F53AF4  (clears both refs + counter)
//   [2] GetSubsystemId override   -> 0x14        (ICF-folded constant return)
//   [3] GetName        override   -> "OpponentManager"  sub_1806FB620
//   [4] GetDebugLabel  inherited  sub_180F54A30
//   [5] GetDebugInfo   override   sub_180F5436C
//   [6] unk_6          inherited  (empty)
//   [7] Update         inherited  (empty for this subsystem)
//   [8] OnTargetChange new        sub_1805D9DB8
//   [9] unk_9          new        (empty)
// ---------------------------------------------------------------------------
class C_CombatActorOpponentManager : public C_CombatActorUpdatedObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorOpponentManager;

    // ---- vtable overrides ----
    ~C_CombatActorOpponentManager() override = default;                         // [0]
    void Reset() override {}                                                     // [1] sub_180F53AF4
    E_CombatSubsystem GetSubsystemId() const override                           // [2] returns 0x14
    { return static_cast<E_CombatSubsystem>(0x14); }
    const char* GetName() const override { return "OpponentManager"; }          // [3] sub_1806FB620
    void GetDebugInfo(void* outInfo) override {}                                // [5] sub_180F5436C

    // ---- new virtuals ----
    // [8] Re-evaluates the owner's current target (state+0xCA0) against the
    // previous (state+0xC98); if changed, gated by CheckOpponent(), commits it
    // via UpdateOpponent(). Also re-fired when m_suppressCounter returns to 0.
    virtual void OnTargetChange() {}                                            // [8] sub_1805D9DB8
    virtual void unk_9() {}                                                     // [9]

    // ---- data members ----

    // +0x18: two exclusive-engagement action holders + flags, built as a
    // 2-element array by the ctor (sub_1804217C8(this+0x18, stride 0x10, 2)).
    // Each holds a _smart_ptr<I_CombatActorAction> (the sync/hunt action that
    // locks this actor to its opponent) -- NOT an opponent target. The smart_ptr
    // copy/assign helpers (sub_1803C33C0 copy-ctor / sub_1803C337C copy-assign)
    // call the action's virtual AddRef (vtable+0x08) / Release (vtable+0x10),
    // supplied by its _i_multithread_reference_target base. Clear: sub_18043229C.
    //   m_lockActions[0] = set by SetLockAction (requested/active lock action)
    //   m_lockActions[1] = exclusive-lock bookkeeping (UpdateOpponent/CheckOpponent)
    // Slot roles are inferred from their writers.
    struct S_ActionLock {
        I_CombatActorActionPtr m_pAction;  // +0x00  _smart_ptr<I_CombatActorAction> (may be null)
        bool                   m_flag;     // +0x08  exclusivity / request flag
        uint8_t                _pad09[7];  // +0x09
    };
    static_assert(sizeof(S_ActionLock) == 0x10);

    S_ActionLock m_lockActions[2];       // +0x18

    int32_t       m_suppressCounter;     // +0x38  CheckOpponent requires == 0
    uint32_t      _pad3C;                // +0x3C
};
static_assert(sizeof(C_CombatActorOpponentManager) == 0x40,
              "C_CombatActorOpponentManager must be 0x40 bytes");

}  // namespace wh::combatmodule
