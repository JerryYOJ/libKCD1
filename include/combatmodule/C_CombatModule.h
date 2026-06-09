#pragma once

#include <cstdint>
#include "../framework/C_BaseModule.h"
#include "../framework/C_Signal.h"

namespace wh::combatmodule {

// Forward declarations
class I_CombatActor;
class C_CombatScene;

// E_CombatSubsystem — subsystem enum for C_CombatActor subsystem array.
// Recovered from sub_180F54EF4 (enum-to-string converter).
enum E_CombatSubsystem : int32_t {
    COMBAT_SUB_BASIC                        = 0x00,
    COMBAT_SUB_MODEL                        = 0x01,
    COMBAT_SUB_DIRECTOR                     = 0x02,
    COMBAT_SUB_ACTION_MANAGER               = 0x03,
    COMBAT_SUB_TRIGGER                      = 0x04,
    COMBAT_SUB_MECHANIC                     = 0x05,
    COMBAT_SUB_ACTOR_ACTION                 = 0x06,
    COMBAT_SUB_ACTOR_ACTION_HELPER          = 0x07,
    COMBAT_SUB_ALIGNMENT                    = 0x08,
    COMBAT_SUB_CONTROLLER                   = 0x09,
    COMBAT_SUB_DEBUG_AI_BRAIN               = 0x0A,
    COMBAT_SUB_PROCEDURAL_CLIP              = 0x0B,
    COMBAT_SUB_CAMERA_CONTROL               = 0x0C,
    COMBAT_SUB_WEAPON_SOLVER                = 0x0D,
    COMBAT_SUB_COLLISION                    = 0x0E,
    COMBAT_SUB_ANIM_COLLISION               = 0x0F,
    COMBAT_SUB_COMBO_MANAGER                = 0x10,
    COMBAT_SUB_RIPOSTE_CHAIN_MANAGER        = 0x11,
    COMBAT_SUB_RESTRICTION                  = 0x12,
    COMBAT_SUB_ENV_MANAGER                  = 0x13,
    COMBAT_SUB_OPPONENT_MANAGER             = 0x14,
    COMBAT_SUB_TIME_COP                     = 0x15,
    COMBAT_SUB_TIME_WARP                    = 0x16,
    COMBAT_SUB_COLLISION_PROCESS            = 0x17,
    COMBAT_SUB_AUTOMATION                   = 0x18,
    COMBAT_SUB_AUTOMATION_ACTION            = 0x19,
    COMBAT_SUB_STEALTH                      = 0x1A,
    COMBAT_SUB_HORSE_PULLDOWN               = 0x1B,
    COMBAT_SUB_HUNT_ATTACK                  = 0x1C,
    COMBAT_SUB_MERCY_KILL                   = 0x1D,
    COMBAT_SUB_VIRTUAL_WEAPON               = 0x1E,
    COMBAT_SUB_EFFECTS                      = 0x1F,
    COMBAT_SUB_TUTORIAL_SLOT_ACTION         = 0x20,
    COMBAT_SUB_NEXT_GUARD_SELECTOR          = 0x21,
    COMBAT_SUB_AIM                          = 0x22,
    COMBAT_SUB_LOOK                         = 0x23,
    COMBAT_SUB_ACTION_FACTORY               = 0x24,
    COMBAT_SUB_UNDEFINED                    = 0x25,
    COMBAT_SUB_BATTLE                       = 0x26,
    COMBAT_SUB_MANNEQUIN                    = 0x27,
    COMBAT_SUB_LAST                         = 0x28,
};

// C_CombatScene — manages active combat actors and their interactions.
// RTTI: .?AVC_CombatScene@combatmodule@wh@@
// Created by C_CombatModule constructor (sub_180FA9680).
// Has three vtable pointers (at +0x00, +0x08, +0x10) and owns a
// sub-object at +0x30 (allocated 0x10 bytes, sub_180FA962C).
//
// Not fully recovered; forward-declared for use by C_CombatModule.
class C_CombatScene;

// C_CombatModule — singleton module owning the combat system.
//
// RTTI: .?AVC_CombatModule@combatmodule@wh@@
// Primary vtable   @ 0x1826b0638
// Secondary vtable @ 0x1826b0688 (I_ModuleMessageListener, at this+0x78)
// Constructor: sub_180F6C660
// Destructor:  sub_180F6D6E4 (cleanup), sub_180F6ECA0 (scalar deleting)
// Size: 0xC8 bytes
//
// Inheritance chain (from RTTI BaseClassArray):
//   C_CombatModule
//     C_BaseModule           (wh::framework)
//       C_Graph              (wh::framework)
//         S_Graph            (wh::framework::internal)
//           S_Job            (wh::framework::internal)
//       I_ModuleMessageListener (wh::framework, at +0x78)
//
// The module is instantiated in the game init factory (sub_18215EB90) which
// allocates 0xC8 bytes and calls the constructor. The resulting pointer is
// stored in the framework's module registry.
//
// === Primary vtable layout (interfuscator-shuffled) ===
//   [0] sub_180F6ECA0  — scalar deleting destructor (frees 0xC8)
//   [1] sub_1806F9E00  — GetModuleId() -> *(uint16_t*)(this+0xA)
//   [2] _guard_check_icall_nop
//   [3] _guard_check_icall_nop
//   [4] sub_180F75108  — Init(): registers CVars, initializes anim slots
//   [5] sub_180F7027C  — PostInit(): registers more CVars (sub_180F702A0)
//   [6] _guard_check_icall_nop
//   [7] sub_1806F8330  — returns 5 (GetSubsystemCount or similar)
//   [8] sub_18020F890  — GetModuleName() -> "CombatModule"
//
// === Secondary vtable (I_ModuleMessageListener, at +0x78) ===
//   [0] sub_180B1A480  — destructor thunk (adjusts this by -0x78)
//   [1] sub_18064E020  — OnModuleMessage(msg): dispatches on msg type
//       Handled message types:
//         0     -> sub_180F7EB18 (level unload / reset)
//         7     -> (entity system notification)
//         10    -> (AI subsystem)
//         0x2E  -> (combat settings reload via CVar)
//         0x30  -> (iterates combat actors)
//         0x31  -> sub_180F7EC50 (entity iteration, cleanup)
//         0x49  -> sub_180F7EC50 (post-level)
//
// === Key global singletons accessed ===
//   Combat settings: 0x1836DD8A0 (accessed via sub_180227B74)
//     CVar init:     sub_180F7514C (0x67d8 bytes — all wh_cs_* CVars)
//     CVar register: sub_180F702A0 (0x2289 bytes — additional CVars)
//   Combat action type database: 0x18359B1E0 (C_CombatActionTypeDatabase singleton)
//     Init:          sub_18071C6E4 — registers action types:
//                    attack, freeAttack, leap, mercyAttack, block, blockMoveBack,
//                    blockStepBack, perfectBlock, perfectNormalBlock, ripostePerfectBlock,
//                    perfectBlockDodge, syncPerfectBlock, syncPerfectBlockHit, syncDodge,
//                    syncDodgeHit, syncRiposte, syncRiposteHit, hitTorso, hitBlockBroken,
//                    hitBlockWeapon, hitMovement, guardIdleUpperBody,
//                    guardSyncMovementMaster/Slave, guardStartSyncMovementMaster/Slave,
//                    movement, guardPreBlock, guardAttackStart, failedAttackOnBlock,
//                    failedAttackOnPB, syncAttack, syncHit, comboAttack, comboHit,
//                    stealthAttackSuccess/Fail, stealthHitSuccess/Fail,
//                    syncTransitionMaster/Slave, huntAttackMaster/Slave,
//                    riderGuard*, freeRiderAttack*, horsePullDown*, group*
//   Animation slot name hashes: initialized by sub_180F46A1C
//                    leftGuard, rightGuard, PerfectBlockSlot, SpecialPerfectBlockSlot,
//                    DodgeSlot, AnimationHit, Dismount, SyncHitStart, Withdraw,
//                    SlotDelay, Attach, etc.
class C_CombatModule : public wh::framework::C_BaseModule {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatModule;
    // ---- Virtual method overrides (interfuscator-shuffled) ----
    ~C_CombatModule() override = default;                                       // [0]
    bool Init() override { return true; }                                       // [4] sub_180F75108
    void PostInit() override {}                                                 // [5] sub_180F7027C
    int GetSubsystemCount() const override { return 5; }                        // [7] sub_1806F8330
    const char* GetModuleName() const override { return "CombatModule"; }       // [8] sub_18020F890

    // ---- C_CombatModule own fields (base ends at +0x88) ----
    wh::shared::C_Signal<I_CombatActor&>    m_onCombatActorChanged;     // +0x88  (0x30 bytes)
    C_CombatScene*                          m_pCombatScene;             // +0xB8  ctor: sub_180FA9680, size 0x40
    // +0xC0: initialized to 0 in constructor (a1[0x18]=0), NOT destroyed
    // in destructor (sub_180F6D6E4). Non-owning scalar value.
    // Purpose unknown but confirmed non-pointer (no cleanup in dtor).
    uint64_t                                m_unknown_C0;               // +0xC0

    static C_CombatModule* GetInstance();            // Offsets.cpp
};
static_assert(sizeof(C_CombatModule) == 0xC8, "C_CombatModule must be 0xC8 bytes");

}  // namespace wh::combatmodule
