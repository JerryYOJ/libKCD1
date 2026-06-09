#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"

namespace wh::combatmodule {

// Forward declarations
class C_CombatActionAttackFactory;
class C_CombatActionPerfectBlockFactory;

// ---------------------------------------------------------------------------
// C_CombatActorActionManager -- manages the active combat action for an actor.
//
// RTTI: .?AVC_CombatActorActionManager@combatmodule@wh@@
// RTTI address: 0x1829f4f00
// vtable: 0x182211df0
// Constructor: sub_1805FD39C
// Destructor (cleanup): sub_1806E4EC4
// Scalar deleting dtor: sub_18060147C (frees 0x60)
// Size: 0x60 bytes
//
// Inherits: C_CombatActorObject (C_CombatActorObject is 0x10 bytes)
// Subsystem: COMBAT_SUB_ACTION_MANAGER (0x03)
//
// This is a per-actor subsystem that:
//   - Owns the two action factories (attack + perfect block)
//   - Tracks the currently active action via ref-counted smart pointers
//   - Coordinates action transitions
//
// Created in sub_1805FDC88 and stored at C_CombatActor+0x720.
//
// The chain *(*(actor+0x720)+0x50) resolves to:
//   actor->m_pActionManager->m_pAttackFactory
//
// === vtable layout (interfuscator-shuffled) ===
//   [0] sub_18060147C  -- scalar deleting destructor (frees 0x60)
//   [1] _guard_check_icall_nop  -- Unknown1 (from C_CombatActorObject)
//   [2] sub_1806F8C40  -- GetSubsystemId: returns 3 (ACTION_MANAGER)
//   [3] sub_1806FA5D0  -- GetName: returns "ActionManager"
//   [4] sub_180F54A30  -- GetDebugLabel (inherited)
//   [5] sub_180F4BE34  -- GetDebugInfo (inherited)
//   [6] (RTTI data)    -- end of vtable
//   [7] sub_1806F3414  -- (scalar deleting dtor for _reference_target, 0x10)
//   [8] sub_18046270C  -- DispatchAction: calls vtable method on action
//   [9] sub_180462790  -- SetActionFlag: sets *(action+0x108) = 1
//
// === Construction details (sub_1805FD39C) ===
//   Base: C_CombatActorObject ctor (sub_180431258) with owning actor
//   +0x00: vtable = C_CombatActorActionManager
//   +0x10: float m_timeScale (init 1.0f via 0x3F800000)
//          then sub_18054BCC4(this+0x10, 8) initializes 0x40 bytes
//          UNVERIFIED: exact layout of +0x10..+0x4F region
//   +0x50: _smart_ptr<C_CombatActionAttackFactory> (created in sub_1806E90B8)
//   +0x58: _smart_ptr<C_CombatActionPerfectBlockFactory> (created in sub_1806E9150)
//
// === Key methods ===
//   DispatchAction (sub_18046270C):
//     Takes (this, actionPtr, targetPtr, flags) and calls the action's
//     primary vtable method at offset +0x10 (Execute/Start).
//
//   SetActionFlag (sub_180462790):
//     Sets byte at action+0x108 to 1, used for sync actions.
//
// === Action creation flow (sub_180460708 / sub_1804605D0) ===
//   1. sub_1804605D0 is the high-level "try to create and dispatch action":
//      a. Checks pre-conditions (sub_180460038)
//      b. Calls sub_180460708 which:
//         - Gets the target C_CombatActor from *(*(actor+0x4B8)+0xCA8)
//         - Checks actor readiness via vtable call *(*(actor))+0x648
//         - Builds transition candidate list via sub_18045E734
//         - Filters candidates via sub_18045F070 (checks transition rules,
//           combat state, distance, and calls the factory at *(target+0x720)+0x50)
//      c. If a valid action is found, allocates 0x128 bytes via sub_180461D80
//         (C_CombatActorActionSyncAttack constructor)
//      d. Stores the action data pointer at action+0xD8
//      e. Sets flags and calls action vtable methods [1] and [2]
//         (AddRef + Start/Init)
//   2. Action object hierarchy for SyncAttack (0x128 bytes):
//      +0x000: primary vtable (C_CombatActorActionSyncAttack)
//      +0x010: secondary vtable (I_CombatActorActionPrivate)
//      +0x0D0: S_CombatActorActionSyncAttackParams vtable
//      +0x0E8: C_CombatActorObject (subsystem back-pointer)
//      +0x100: C_Signal member
//      +0x108: secondary vtable #2
//      +0x110: sub-object pointer (0x38 bytes, sub_180462224)
//      +0x118: sub-object pointer (0x18 bytes, sub_180431144)
//      +0x120: bool flag
// ---------------------------------------------------------------------------
class C_CombatActorActionManager : public C_CombatActorObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorActionManager;
    // ---- Virtual method overrides ----
    ~C_CombatActorActionManager() override = default;               // [0]

    E_CombatSubsystem GetSubsystemId() const override               // [2]
    { return COMBAT_SUB_ACTION_MANAGER; }

    const char* GetName() const override                            // [3]
    { return "ActionManager"; }

    // ---- Data members ----

    // +0x10..+0x4F: Action management state block (0x40 bytes)
    // Initialized by sub_18054BCC4(this+0x10, 8).
    // First 4 bytes are a float (m_timeScale = 1.0f).
    // UNVERIFIED: exact field breakdown of remaining 0x3C bytes.
    // Likely contains: current action smart_ptr, pending action, transition state.
    float               m_timeScale;        // +0x10  (init 1.0f)
    uint32_t            _pad14;             // +0x14
    uint64_t            m_actionState18;    // +0x18  initialized by sub_18024B0E8
    uint64_t            m_unknown20;        // +0x20  (init 0, UNVERIFIED)
    uint64_t            m_unknown28;        // +0x28  (init 0, UNVERIFIED)
    uint64_t            m_unknown30;        // +0x30  (init 0, UNVERIFIED)
    uint64_t            m_unknown38;        // +0x38  (init 0, UNVERIFIED)
    uint64_t            m_unknown40;        // +0x40  (UNVERIFIED)
    uint64_t            m_unknown48;        // +0x48  (UNVERIFIED)

    // +0x50: smart pointer to C_CombatActionAttackFactory
    // Created in sub_1806E90B8: allocates 0x10, calls C_CombatActorObject ctor,
    // then sets vtable to C_CombatActionAttackFactory.
    // VERIFIED: this is how *(*(actor+0x720)+0x50) resolves to the factory.
    C_CombatActionAttackFactory*        m_pAttackFactory;           // +0x50

    // +0x58: smart pointer to C_CombatActionPerfectBlockFactory
    // Created in sub_1806E9150: same pattern as attack factory.
    C_CombatActionPerfectBlockFactory*  m_pPerfectBlockFactory;     // +0x58
};
static_assert(sizeof(C_CombatActorActionManager) == 0x60,
    "C_CombatActorActionManager must be 0x60 bytes");

}  // namespace wh::combatmodule
