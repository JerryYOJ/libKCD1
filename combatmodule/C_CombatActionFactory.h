#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatActionFactoryBase -- base class for combat action factories.
//
// RTTI: .?AVC_CombatActionFactoryBase@combatmodule@wh@@
// RTTI address: 0x1829f07b0
// Inherits: C_CombatActorObject
// Size: 0x10 bytes (same as C_CombatActorObject, no additional members)
//
// The factory is a per-actor subsystem (NOT a singleton).
// Each C_CombatActor creates its own action factory instances during
// initialization in sub_1805FDC88.
//
// C_CombatActorObject vtable provides:
//   GetSubsystemId() -> 0x24 (COMBAT_SUB_ACTION_FACTORY)    [sub_1806FA6A0]
//   GetName()        -> "CombatActioFactory" (typo in binary) [sub_1806FA530]
//
// Two concrete factory subclasses are created per actor:
//   1. C_CombatActionAttackFactory  -- creates attack actions
//   2. C_CombatActionPerfectBlockFactory -- creates perfect block actions
//
// The factory is accessed via the action manager:
//   *(*(actor+0x720))+0x50  resolves to:
//     actor->m_pActionManager->m_pAttackFactory  (at manager+0x50)
//
// Factory vtable layout (shared base with per-type override at [6]):
//   [0] sub_1806E4F5C  -- scalar deleting destructor (frees 0x10)
//   [1] _guard_check_icall_nop  -- Unknown1 (from C_CombatActorObject)
//   [2] sub_1806FA6A0  -- GetSubsystemId: returns 0x24
//   [3] sub_1806FA530  -- GetName: returns "CombatActioFactory"
//   [4] sub_180F54A30  -- GetDebugLabel
//   [5] sub_180F4BE34  -- GetDebugInfo
//   [6] (varies)       -- CreateAction: override per factory type
//
// NOTE: Slot order is interfuscator-shuffled; indices above are NOT stable.
// ---------------------------------------------------------------------------
class C_CombatActionFactoryBase : public C_CombatActorObject {
public:
    ~C_CombatActionFactoryBase() override = default;

    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_ACTION_FACTORY; }
    const char* GetName() const override { return "CombatActioFactory"; }

    virtual void* CreateAction() = 0;                                // [6] pure, overridden per factory type
};
static_assert(sizeof(C_CombatActionFactoryBase) == 0x10);

// ---------------------------------------------------------------------------
// C_CombatActionAttackFactory -- factory for attack actions.
//
// RTTI: .?AVC_CombatActionAttackFactory@combatmodule@wh@@
// vtable: 0x1822157e8
// Constructor: created in sub_1806E90B8
// Size: 0x10 (no additional members beyond base)
//
// Created during C_CombatActorActionManager construction (sub_1805FD39C).
// Stored at C_CombatActorActionManager+0x50 (m_pAttackFactory).
// ---------------------------------------------------------------------------
class C_CombatActionAttackFactory : public C_CombatActionFactoryBase {
public:
    ~C_CombatActionAttackFactory() override = default;
    // CreateAction override at vtable[6] = sub_182447370 region
};
static_assert(sizeof(C_CombatActionAttackFactory) == 0x10);

// ---------------------------------------------------------------------------
// C_CombatActionPerfectBlockFactory -- factory for perfect block actions.
//
// RTTI: .?AVC_CombatActionPerfectBlockFactory@combatmodule@wh@@
// vtable: 0x182215820
// Constructor: created in sub_1806E9150
// Size: 0x10 (no additional members beyond base)
//
// Created during C_CombatActorActionManager construction (sub_1805FD39C).
// Stored at C_CombatActorActionManager+0x58 (m_pPerfectBlockFactory).
// ---------------------------------------------------------------------------
class C_CombatActionPerfectBlockFactory : public C_CombatActionFactoryBase {
public:
    ~C_CombatActionPerfectBlockFactory() override = default;
    // CreateAction override at vtable[6] = sub_1824406B0 region
};
static_assert(sizeof(C_CombatActionPerfectBlockFactory) == 0x10);

}  // namespace wh::combatmodule
