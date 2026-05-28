#pragma once

// ==========================================================================
// S_CombatSettings.h
//
// Combat settings singleton for KCD (Kingdom Come: Deliverance)
// Singleton instance at: 0x1836DD8A0
// Getter function: sub_180227B74
// CVar init function: sub_180F7514C
//
// Reverse engineered from wh_cs_* CVar registrations.
// Parameter 'a1' is _QWORD* so:
//   a1 + N  = byte offset N * 8   (QWORD pointer arithmetic)
//   (__int64)a1 + N = byte offset N  (raw byte offset)
//
// Fields stored as ICVar* pointers (from RegisterString/vtable+0x10)
// are 8-byte pointers at QWORD-indexed offsets.
//
// Registration patterns:
//   vtable+0x40: RegisterCVar(name, &var, default, flags, help, changeFn, allowModify)
//   vtable+0x48: Simple register(name, &storage)
//   vtable+0x10: RegisterString -> returns ICVar* stored in struct
//   vtable+0x108: RegisterCommand -> no struct storage
// ==========================================================================

#include <cstdint>

namespace wh::combatmodule {

#pragma pack(push, 1)
struct S_CombatSettings {
    // --- offset 0x000 (a1 + 0 = a1, QWORD-indexed) ---
    int32_t  wh_cs_DebugDrawAttackActions;          // 0x000  // "Enable visual debug of attack actions." (default=0, flags=4)

    uint8_t  _pad_004[0x4];                         // 0x004

    // --- offset 0x008 (a1[1]) ---
    int64_t  pCVar_wh_cs_DebugDrawQuery;            // 0x008  // ICVar* "Show query debug for specified actor."

    // --- offset 0x010 (a1 + 2) ---
    float    wh_cs_TimeWarpFadeIn;                  // 0x010  // vtable+0x48

    // --- offset 0x014 ((__int64)a1 + 0x14) ---
    float    wh_cs_TimeWarpFadeOut;                 // 0x014  // vtable+0x48

    // --- offset 0x018 (a1 + 3) ---
    float    wh_cs_TimeWarpDuration;                // 0x018  // vtable+0x48

    // --- offset 0x01C ((__int64)a1 + 0x1C) ---
    float    wh_cs_TimeWarpBias;                    // 0x01C  // vtable+0x48

    // --- offset 0x020 (a1 + 4) ---
    float    wh_cs_TimeWarpPBFadeSpeedForPlayer;    // 0x020  // vtable+0x48

    // --- offset 0x024 ((__int64)a1 + 0x24) ---
    float    wh_cs_TimeWarpPBFadeSpeedForOpp;       // 0x024  // vtable+0x48

    // --- offset 0x028 (a1 + 5) ---
    float    wh_cs_TimeWarpDodgeFadeSpeedForPlayer; // 0x028  // vtable+0x48

    // --- offset 0x02C ((__int64)a1 + 0x2C) ---
    float    wh_cs_TimeWarpDodgeFadeSpeedForOpp;    // 0x02C  // vtable+0x48

    // --- offset 0x030 (a1 + 6) ---
    float    wh_cs_RiposteSlotDuration;             // 0x030  // vtable+0x48

    // --- offset 0x034 ((__int64)a1 + 0x34) ---
    float    wh_cs_PerfectBlock_RetargetAngleFOVBias; // 0x034 // vtable+0x48

    // --- offset 0x038 (a1 + 7) ---
    float    wh_cs_PerfectBlock_SpatialVolumeRadius; // 0x038 // vtable+0x48

    // --- offset 0x03C ((__int64)a1 + 0x3C) ---
    float    wh_cs_Dodge_WindowMod;                 // 0x03C  // vtable+0x48

    // --- offset 0x040 (a1 + 8) ---
    float    wh_cs_Dodge_SpatialTimeLimit;          // 0x040  // vtable+0x48

    // --- offset 0x044 ((__int64)a1 + 0x44) ---
    int32_t  wh_cs_Dodge_IgnoreCollision;           // 0x044  // "When nonzero dodging actor will ignore weapon collision..." (default=1, flags=2)

    // --- offset 0x048 (a1 + 9) ---
    float    wh_cs_AISlotDurationMod;               // 0x048  // vtable+0x48

    // --- offset 0x04C ((__int64)a1 + 0x4C) ---
    float    wh_cs_PLSlotDurationMod;               // 0x04C  // vtable+0x48

    // --- offset 0x050 (a1 + 0xA) ---
    float    wh_cs_BlockCooldown;                   // 0x050  // vtable+0x48

    // --- offset 0x054 ((__int64)a1 + 0x54) ---
    float    wh_cs_StaticAttackCooldown;            // 0x054  // vtable+0x48

    // --- offset 0x058 (a1 + 0xB) ---
    float    wh_cs_MoveCooldown;                    // 0x058  // vtable+0x48

    // --- offset 0x05C ((__int64)a1 + 0x5C) ---
    int32_t  wh_cs_EnableRiposteChains;             // 0x05C  // "Enabled riposte chains." (default=0, flags=2)

    // --- offset 0x060 (a1 + 0xC) ---
    int32_t  wh_cs_EnableRipostePerfectBlock;       // 0x060  // "Enabled riposte perfect blocs..." (default=1, flags=2)

    // --- offset 0x064 ((__int64)a1 + 0x64) ---
    float    wh_cs_RipostePerfectBlockZoneDistance; // 0x064  // vtable+0x48

    // --- offset 0x068 (a1 + 0xD) ---
    float    wh_cs_PlayerInputMouseZoneChangeSensitivity; // 0x068 // vtable+0x48

    // --- offset 0x06C ((__int64)a1 + 0x6C) ---
    int32_t  wh_cs_PlayerInputMouseUnlocking;       // 0x06C  // "Enable mouse movement unlocking for player" (default=1, flags=4)

    // --- offset 0x070 (a1 + 0xE) ---
    int32_t  wh_cs_PlayerInputMouseZoneSelectionMode; // 0x070 // "Mode for changing zones with mouse..." (default=0, flags=4)

    // --- offset 0x074 ((__int64)a1 + 0x74) ---
    int32_t  wh_cs_PlayerInputBypass;               // 0x074  // "Disables combat input" (default=0, flags=4)

    // --- offset 0x078 (a1 + 0xF) ---
    float    wh_cs_PlayerInputLockingTolerance;     // 0x078  // vtable+0x48

    // --- offset 0x07C ((__int64)a1 + 0x7C) ---
    float    wh_cs_PlayerMaxOpponentDistanceToLock; // 0x07C  // vtable+0x48

    // --- offset 0x080 (a1 + 0x10) ---
    float    wh_cs_PlayerLockOpponentAngleBias;     // 0x080  // vtable+0x48

    // --- offset 0x084 ((__int64)a1 + 0x84) ---
    float    wh_cs_PlayerMaxOpponentDistanceToUnlock; // 0x084 // vtable+0x48

    // --- offset 0x088 (a1 + 0x11) ---
    float    wh_cs_PlayerMaxOpponentAngleToUnlock;  // 0x088  // vtable+0x48

    // --- offset 0x08C ((__int64)a1 + 0x8C) ---
    float    wh_cs_PlayerMaxOpponentAngleToLock;    // 0x08C  // vtable+0x48

    // --- offset 0x090 (a1 + 0x12) ---
    float    wh_cs_PlayerUnlockTimeout;             // 0x090  // vtable+0x48

    // --- offset 0x094 ((__int64)a1 + 0x94) ---
    int32_t  wh_cs_PlayerLockDisabled;              // 0x094  // "Disables player locking functionality." (default=0, flags=4)

    // --- offset 0x098 (a1 + 0x13) ---
    float    wh_cs_PlayerInputMouseZoneChangeMinTime; // 0x098 // vtable+0x48

    // --- offset 0x09C ((__int64)a1 + 0x9C) ---
    float    wh_cs_PlayerInputMouseZoneChangeMinDistance; // 0x09C // vtable+0x48

    // --- offset 0x0A0 (a1 + 0x14) ---
    float    wh_cs_PlayerInputMouseUnlockMinTime;   // 0x0A0  // vtable+0x48

    // --- offset 0x0A4 ((__int64)a1 + 0xA4) ---
    float    wh_cs_PlayerInputMouseUnlockReturnTime; // 0x0A4 // vtable+0x48

    // --- offset 0x0A8 (a1 + 0x15) ---
    float    wh_cs_PlayerInputGamepadUnlockReturnTime; // 0x0A8 // vtable+0x48

    // --- offset 0x0AC ((__int64)a1 + 0xAC) ---
    float    wh_cs_PlayerInputMouseUnlockMinDistanceToUnlock; // 0x0AC // vtable+0x48

    // --- offset 0x0B0 (a1 + 0x16) ---
    float    wh_cs_PlayerInputMouseUnlockMinOppAngle; // 0x0B0 // vtable+0x48

    // --- offset 0x0B4 ((__int64)a1 + 0xB4) ---
    float    wh_cs_PlayerInputMouseUnlockZThreshold; // 0x0B4 // vtable+0x48

    // --- offset 0x0B8 (a1 + 0x17) ---
    float    wh_cs_PlayerInputMouseUnlockXThreshold; // 0x0B8 // vtable+0x48

    // --- offset 0x0BC ((__int64)a1 + 0xBC) ---
    float    wh_cs_PlayerInputGamepadUnlockMinTime; // 0x0BC  // vtable+0x48

    // --- offset 0x0C0 (a1 + 0x18) ---
    float    wh_cs_PlayerInputGamepadUnlockMinTimeSameZone; // 0x0C0 // vtable+0x48

    // --- offset 0x0C4 ((__int64)a1 + 0xC4) ---
    float    wh_cs_PlayerInputGamepadUnlockMinDistanceToUnlock; // 0x0C4 // vtable+0x48

    // --- offset 0x0C8 (a1 + 0x19) ---
    float    wh_cs_PlayerInputLockAreaWidth;        // 0x0C8  // vtable+0x48

    // --- offset 0x0CC ((__int64)a1 + 0xCC) ---
    float    wh_cs_PlayerInputLockAreaWidthNoCombat; // 0x0CC // vtable+0x48

    // --- offset 0x0D0 (a1 + 0x1A) ---
    float    wh_cs_PlayerInputUnlockAreaWidthHyst;  // 0x0D0  // vtable+0x48

    // --- offset 0x0D4 ((__int64)a1 + 0xD4) ---
    float    wh_cs_PlayerInputGamepadSensitivity;   // 0x0D4  // vtable+0x48

    // --- offset 0x0D8 (a1 + 0x1B) ---
    float    wh_cs_PlayerInputMouseSensitivity;     // 0x0D8  // vtable+0x48

    // --- offset 0x0DC ((__int64)a1 + 0xDC) ---
    float    wh_cs_PlayerInputCursorUnlockDistance; // 0x0DC  // vtable+0x48

    // --- offset 0x0E0 (a1 + 0x1C) ---
    float    wh_cs_PlayerInputCombatUnlockDelay;    // 0x0E0  // vtable+0x48

    // --- offset 0x0E4 ((__int64)a1 + 0xE4) ---
    float    wh_cs_PlayerMountedPitchThreshold;     // 0x0E4  // vtable+0x48

    // --- offset 0x0E8 (a1 + 0x1D) ---
    int32_t  wh_cs_DebugDrawPlayerInput;            // 0x0E8  // "Enable visual debug of player input." (default=0, flags=4)

    // --- offset 0x0EC ((__int64)a1 + 0xEC) ---
    int32_t  wh_cs_PlayerTutorialStep;              // 0x0EC  // "Debugger trigger of combat tutorial step. [1-?, 0 disabled]" (default=0, flags=4)

    // --- offset 0x0F0 (a1 + 0x1E) ---
    float    wh_cs_PlayerHorizontalUnlockDelay;     // 0x0F0  // vtable+0x48

    // --- offset 0x0F4 ((__int64)a1 + 0xF4) ---
    float    wh_cs_PlayerVerticalUnlockDelay;       // 0x0F4  // vtable+0x48

    // --- offset 0x0F8 (a1 + 0x1F) ---
    float    wh_cs_PlayerAttackInactivityDuration;  // 0x0F8  // vtable+0x48

    // --- offset 0x0FC ((__int64)a1 + 0xFC) ---
    float    wh_cs_FreeBlockPreparingDuration;      // 0x0FC  // vtable+0x48

    // --- offset 0x100 (a1 + 0x20) ---
    int32_t  wh_cs_TargetUseSpineBone;              // 0x100  // "Uses spine3 for targeting opponent." (default=0, flags=4)

    // --- offset 0x104 ((__int64)a1 + 0x104) ---
    float    wh_cs_TutorialSlotActionFadeIn;        // 0x104  // vtable+0x48

    // --- offset 0x108 (a1 + 0x21) ---
    float    wh_cs_TutorialSlotActionFadeOut;       // 0x108  // vtable+0x48

    // --- offset 0x10C ((__int64)a1 + 0x10C) ---
    float    wh_cs_ComboSlotDuration;               // 0x10C  // vtable+0x48

    // --- offset 0x110 (a1 + 0x22) ---
    float    wh_cs_WindowMinWeight;                 // 0x110  // vtable+0x48

    // --- offset 0x114 ((__int64)a1 + 0x114) ---
    int32_t  wh_cs_PLSkillProfile;                  // 0x114  // "Skill profile for player." (default=1, flags=2)

    // --- offset 0x118 (a1 + 0x23) ---
    int32_t  wh_cs_AISkillProfile;                  // 0x118  // "Skill profile for AI." (default=1, flags=2)

    // --- offset 0x11C ((__int64)a1 + 0x11C) ---
    float    wh_cs_StealthActionDistance;           // 0x11C  // vtable+0x48

    // --- offset 0x120 (a1 + 0x24) ---
    float    wh_cs_StealthActionAngle;              // 0x120  // vtable+0x48

    // --- offset 0x124 ((__int64)a1 + 0x124) ---
    float    wh_cs_StealthActionLyingAngle;         // 0x124  // vtable+0x48

    // --- offset 0x128 (a1 + 0x25) ---
    float    wh_cs_StealthActionMaxAngle;           // 0x128  // vtable+0x48

    // --- offset 0x12C ((__int64)a1 + 0x12C) ---
    float    wh_cs_HorsePullDownAngle;              // 0x12C  // vtable+0x48

    // --- offset 0x130 (a1 + 0x26) ---
    float    wh_cs_HorsePullDownZeroAngle;          // 0x130  // vtable+0x48

    // --- offset 0x134 ((__int64)a1 + 0x134) ---
    float    wh_cs_HorsePullDownZAngle;             // 0x134  // vtable+0x48

    // --- offset 0x138 (a1 + 0x27) ---
    int32_t  wh_cs_HuntAttackAttackerMinLogical;    // 0x138  // "Minimal pseudospeed of attacker..." (default=0, flags=2)
                                                    //         UNVERIFIED: help text says "pseudospeed" which could be float;
                                                    //         registered via vtable+0x40 with default 0 as int

    // --- offset 0x13C ((__int64)a1 + 0x13C) ---
    int32_t  wh_cs_HuntAttackVictimMinLogical;      // 0x13C  // "Minimal pseudospeed of victim..." (default=1, flags=2)

    // --- offset 0x140 (a1 + 0x28) ---
    int32_t  wh_cs_HuntAttackDisableVelocity;       // 0x140  // "Disable velocity checks for debugging." (default=0, flags=2)

    // --- offset 0x144 ((__int64)a1 + 0x144) ---
    float    wh_cs_HuntAttackMoveWeight;            // 0x144  // vtable+0x48

    // --- offset 0x148 (a1 + 0x29) ---
    float    wh_cs_HuntAttackFwdAngleLimit;         // 0x148  // vtable+0x48

    // --- offset 0x14C ((__int64)a1 + 0x14C) ---
    int32_t  wh_cs_HuntAttackDebugMode;             // 0x14C  // "Debug mode that all input conditions are skipped." (default=0, flags=2)

    // --- offset 0x150 (a1 + 0x2A) ---
    int32_t  wh_cs_DebugSwitch;                     // 0x150  // "General combat debug switch" (default=0, flags=2)

    uint8_t  _pad_154[0x4];                         // 0x154

    // --- offset 0x158 (a1[0x2B] = a1 + 0x2B) ---
    int64_t  pCVar_wh_cs_DebugInfo;                 // 0x158  // ICVar* "Enable combat system debug info..."

    // --- offset 0x160 (a1 + 0x2C) ---
    int32_t  wh_cs_DebugPhys;                       // 0x160  // "Enable combat system debug info for physics" (default=0, flags=2)

    // --- offset 0x164 ((__int64)a1 + 0x164) ---
    float    wh_cs_DebugInfoPosY;                   // 0x164  // vtable+0x48

    // --- offset 0x168 (a1 + 0x2D) ---
    int32_t  wh_cs_HitReactions;                    // 0x168  // "Enables combat hit reactions" (default=0, flags=2)

    // --- offset 0x16C ((__int64)a1 + 0x16C) ---
    int32_t  wh_cs_DisableScripts;                  // 0x16C  // "Disables Lua scripts - movement." (default=0, flags=2)

    // --- offset 0x170 (a1 + 0x2E) ---
    float    wh_cs_PosAlignmentInterruptionZAngleThreshold; // 0x170 // vtable+0x48

    // --- offset 0x174 ((__int64)a1 + 0x174) ---
    int32_t  wh_cs_PhysSim;                         // 0x174  // "Physical simulation." (default=0, flags=2)

    // --- offset 0x178 (a1 + 0x2F) ---
    float    wh_cs_PhysWeaponColSim_ImpactCoef;     // 0x178  // vtable+0x48

    // --- offset 0x17C ((__int64)a1 + 0x17C) ---
    float    wh_cs_PhysHitReaction_ImpactCoef;      // 0x17C  // vtable+0x48

    // --- offset 0x180 (a1 + 0x30) ---
    float    wh_cs_PhysWeaponHitReaction_ImpactCoef; // 0x180 // vtable+0x48

    // --- offset 0x184 ((__int64)a1 + 0x184) ---
    float    wh_cs_BlockWithdrawalBlendWeightLoss;  // 0x184  // vtable+0x48

    // --- offset 0x188 (a1 + 0x31) ---
    float    wh_cs_AIAttackInterval;                // 0x188  // vtable+0x48

    // --- offset 0x18C ((__int64)a1 + 0x18C) ---
    float    wh_cs_AIAttackFiglProb;                // 0x18C  // vtable+0x48

    // --- offset 0x190 (a1 + 0x32) ---
    int32_t  wh_cs_DebugDisableRiposteSlot;         // 0x190  // "Disables ripostes. All ripostes will be triggered." (default=1, flags=2)

    // --- offset 0x194 ((__int64)a1 + 0x194) ---
    int32_t  wh_cs_OpponentManagerBruteForce;       // 0x194  // "Iterate through all actors! (AI grid wont be used)" (default=0, flags=2)

    // --- offset 0x198 (a1 + 0x33) ---
    int32_t  wh_cs_ShowCombatUI;                    // 0x198  // "Enabled combat UI for testing purposes." (default=1, flags=2)

    // --- offset 0x19C ((__int64)a1 + 0x19C) ---
    int32_t  wh_cs_ShowComboZonesUI;                // 0x19C  // "Show combo zones on combat cross." (default=1, flags=2)

    // --- offset 0x1A0 (a1 + 0x34) ---
    int32_t  wh_cs_Profiling;                       // 0x1A0  // "Enabled profiling in combat..." (default=0, flags=2)

    // --- offset 0x1A4 ((__int64)a1 + 0x1A4) ---
    float    wh_cs_CombatCapsuleWidth;              // 0x1A4  // vtable+0x48

    // --- offset 0x1A8 (a1 + 0x35) ---
    float    wh_cs_CombatCapsulePosZ;               // 0x1A8  // vtable+0x48

    // --- offset 0x1AC ((__int64)a1 + 0x1AC) ---
    float    wh_cs_PreBlockRestartCooldown;         // 0x1AC  // vtable+0x48

    // --- offset 0x1B0 (a1 + 0x36) ---
    int32_t  wh_cs_EnableCollisionResizing;         // 0x1B0  // "Enables to enlarge capsule collision in combat mode." (default=0, flags=2)

    // --- offset 0x1B4 ((__int64)a1 + 0x1B4) ---
    int32_t  wh_cs_AIForceSymetric;                 // 0x1B4  // "Force AI to get symetric force zone." (default=0, flags=2)

    // --- offset 0x1B8 (a1 + 0x37) ---
    int32_t  wh_cs_ForceZone;                       // 0x1B8  // "Force combat zone selection by: -1 - disabled, 0-4 zones z0-z4" (default=-1, flags=2)

    // --- offset 0x1BC ((__int64)a1 + 0x1BC) ---
    int32_t  wh_cs_ForceGuardStance;                // 0x1BC  // "Force guard stance selection by: -1 - disabled, 0 - left, 1 - right" (default=-1, flags=2)

    // --- offset 0x1C0 (a1 + 0x38) ---
    int32_t  wh_cs_DebugAI;                         // 0x1C0  // "Enables debug AI" (default=0, flags=2, changeFunc=sub_180F7CD78)

    // --- offset 0x1C4 ((__int64)a1 + 0x1C4) ---
    int32_t  wh_cs_DebugAIForcePlayer;              // 0x1C4  // "Force debug AI to select player as opponent" (default=0, flags=2)

    // --- offset 0x1C8 (a1 + 0x39) ---
    int32_t  wh_cs_AIForceBlock;                    // 0x1C8  // "Force AI to block by: 0-disabled, 1-normal, 2-perfect, 3-no block, 4-broken" (default=0, flags=2)

    // --- offset 0x1CC ((__int64)a1 + 0x1CC) ---
    int32_t  wh_cs_AIForceDodge;                    // 0x1CC  // "Force AI to dodge by: 0-disabled, 1-back, 2-right, 3-left" (default=0, flags=2)

    // --- offset 0x1D0 (a1 + 0x3A) ---
    int32_t  wh_cs_AIForceSyncPerfectBlock;         // 0x1D0  // "Force AI to make special riposte." (default=0, flags=2)

    // --- offset 0x1D4 ((__int64)a1 + 0x1D4) ---
    int32_t  wh_cs_AIForceBlockMode;                // 0x1D4  // "Force AI block mode trigger" (default=0, flags=2)

    // --- offset 0x1D8 (a1 + 0x3B) ---
    int32_t  wh_cs_AIForceAttack;                   // 0x1D8  // "Force AI to Attack by: 0-disabled, 1-riposte, 2-attack every 8s..." (default=0, flags=2)

    // --- offset 0x1DC ((__int64)a1 + 0x1DC) ---
    int32_t  wh_cs_AIReblockMode;                   // 0x1DC  // "AI reblock mode: 0-never, 1-always, 2-random 50% chance" (default=0, flags=2)

    // --- offset 0x1E0 (a1 + 0x3C) ---
    int32_t  wh_cs_AIForceProfile;                  // 0x1E0  // "Force AI brain profile from table." (default=1, flags=2)

    // --- offset 0x1E4 ((__int64)a1 + 0x1E4) ---
    int32_t  wh_cs_AIMoveMode;                      // 0x1E4  // "AI Move mode: 1-None, 2-Around, 3-Pursuit" (default=1, flags=2)

    // --- offset 0x1E8 (a1 + 0x3D) ---
    float    wh_cs_AIMoveSpeed;                     // 0x1E8  // vtable+0x48

    // --- offset 0x1EC ((__int64)a1 + 0x1EC) ---
    float    wh_cs_AIMoveTimer;                     // 0x1EC  // vtable+0x48

    // --- offset 0x1F0 (a1 + 0x3E) ---
    float    wh_cs_AIMoveDistance;                   // 0x1F0  // vtable+0x48

    // --- offset 0x1F4 ((__int64)a1 + 0x1F4) ---
    float    wh_cs_AIDelayedBlock;                  // 0x1F4  // vtable+0x48

    // --- offset 0x1F8 (a1 + 0x3F) ---
    float    wh_cs_AIDelayedBlockInSlot;            // 0x1F8  // vtable+0x48

    // --- offset 0x1FC ((__int64)a1 + 0x1FC) ---
    float    wh_cs_PLDelayedBlockInSlot;            // 0x1FC  // vtable+0x48

    // --- offset 0x200 (a1 + 0x40) ---
    float    wh_cs_PLDelayedRiposteInSlot;          // 0x200  // vtable+0x48

    // --- offset 0x204 ((__int64)a1 + 0x204) ---
    float    wh_cs_PLDelayedSPBlockInSlot;          // 0x204  // vtable+0x48

    // --- offset 0x208 (a1 + 0x41) ---
    float    wh_cs_AIDelayedRiposteInSlot;          // 0x208  // vtable+0x48

    // --- offset 0x20C ((__int64)a1 + 0x20C) ---
    int32_t  wh_cs_PLForcePerfectBlock;             // 0x20C  // "Player always trigger PB when holds block." (default=0, flags=2)

    // --- offset 0x210 (a1 + 0x42) ---
    int32_t  wh_cs_AllForceComboId;                 // 0x210  // "When any body attacks he will perform combo attack given by ComboId." (default=0, flags=2)

    uint8_t  _pad_214[0x4];                         // 0x214

    // --- offset 0x218 (a1[0x43]) ---
    int64_t  pCVar_wh_cs_DebugOpponent;             // 0x218  // ICVar* "Set debug opponent which can then controlled with a keyboard."

    // --- offset 0x220 (a1 + 0x44) ---
    float    wh_cs_AIDistanceTolerance;             // 0x220  // vtable+0x48

    // --- offset 0x224 ((__int64)a1 + 0x224) ---
    float    wh_cs_PlayerDistanceTolerance;         // 0x224  // vtable+0x48

    // --- offset 0x228 (a1 + 0x45) ---
    float    wh_cs_MaxAttackDistanceMoveOffset;     // 0x228  // vtable+0x48

    // --- offset 0x22C ((__int64)a1 + 0x22C) ---
    float    wh_cs_MaxAttackDistanceMoveOffsetStiffness; // 0x22C // vtable+0x48

    // --- offset 0x230 (a1 + 0x46) ---
    int32_t  wh_cs_MaxAttackDistanceDebug;          // 0x230  // "Debug draw for max attack distance." (default=0, flags=2)

    // --- offset 0x234 ((__int64)a1 + 0x234) ---
    float    wh_cs_MaxAttackRotationDeviation;      // 0x234  // vtable+0x48

    // --- offset 0x238 (a1 + 0x47) ---
    float    wh_cs_AttackTimeToHitEst;              // 0x238  // vtable+0x48

    // --- offset 0x23C ((__int64)a1 + 0x23C) ---
    float    wh_cs_SyncGuardAutoTriggerMinVelocity; // 0x23C  // vtable+0x48

    // --- offset 0x240 (a1 + 0x48) ---
    float    wh_cs_SyncGuardAutoTriggerMaxVelocity; // 0x240  // vtable+0x48

    // --- offset 0x244 ((__int64)a1 + 0x244) ---
    float    wh_cs_SyncGuardAutoTriggerMoveWeight;  // 0x244  // vtable+0x48

    // --- offset 0x248 (a1 + 0x49) ---
    float    wh_cs_SyncGuardMaxAngle;               // 0x248  // vtable+0x48

    // --- offset 0x24C ((__int64)a1 + 0x24C) ---
    float    wh_cs_SyncGuardkDistanceTolerance;     // 0x24C  // vtable+0x48

    // --- offset 0x250 (a1 + 0x4A) ---
    float    wh_cs_LockedAttackMaxAngle;            // 0x250  // vtable+0x48

    // --- offset 0x254 ((__int64)a1 + 0x254) ---
    float    wh_cs_LogicalBlockMaxAngle;            // 0x254  // vtable+0x48

    // --- offset 0x258 (a1 + 0x4B) ---
    float    wh_cs_LockedAttackZTolerance;          // 0x258  // vtable+0x48

    // --- offset 0x25C ((__int64)a1 + 0x25C) ---
    float    wh_cs_LockedAttackDistanceTolerance;   // 0x25C  // vtable+0x48

    // --- offset 0x260 (a1 + 0x4C) ---
    float    wh_cs_IntentionalTargetAngleDefault;   // 0x260  // vtable+0x48

    // --- offset 0x264 ((__int64)a1 + 0x264) ---
    float    wh_cs_IntentionalTargetAngleMin;       // 0x264  // vtable+0x48

    // --- offset 0x268 (a1 + 0x4D) ---
    float    wh_cs_IntentionalTargetAngleMax;       // 0x268  // vtable+0x48

    // --- offset 0x26C ((__int64)a1 + 0x26C) ---
    int32_t  wh_cs_IntentionalTargetAngleLimitOpponentCount; // 0x26C // vtable+0x48
                                                    //         UNVERIFIED type: could be int or float

    // --- offset 0x270 (a1 + 0x4E) ---
    float    wh_cs_IntentionalTargetAngleRadius;    // 0x270  // vtable+0x48

    // --- offset 0x274 ((__int64)a1 + 0x274) ---
    float    wh_cs_RepeatHitTimeout;                // 0x274  // vtable+0x48

    // --- offset 0x278 (a1 + 0x4F) ---
    float    wh_cs_CanAlmostHitOffset;              // 0x278  // vtable+0x48

    // --- offset 0x27C ((__int64)a1 + 0x27C) ---
    float    wh_cs_NoCombatUnarmedAlignmentOffset;  // 0x27C  // vtable+0x48

    // --- offset 0x280 (a1 + 0x50) ---
    float    wh_cs_DogClinchOpponentAlignmentOffset; // 0x280 // vtable+0x48

    // --- offset 0x284 ((__int64)a1 + 0x284) ---
    int32_t  wh_cs_UnarmedTargetToHeadBone;         // 0x284  // "Rotation alignment target headbone instead of reference." (default=1, flags=2)

    // --- offset 0x288 (a1 + 0x51) ---
    int32_t  wh_cs_OnlyBigTurns;                    // 0x288  // "Use only big turns animations during combat." (default=0, flags=2)

    // --- offset 0x28C ((__int64)a1 + 0x28C) ---
    float    wh_cs_ForceTurnAngleThreshold;         // 0x28C  // vtable+0x48

    // --- offset 0x290 (a1 + 0x52) ---
    float    wh_cs_BigTurnThreshold;                // 0x290  // vtable+0x48

    // --- offset 0x294 ((__int64)a1 + 0x294) ---
    float    wh_cs_MinimalTurnThreshold;            // 0x294  // vtable+0x48

    // --- offset 0x298 (a1 + 0x53) ---
    float    wh_cs_MinimalTurnThresholdByTime;      // 0x298  // vtable+0x48

    // --- offset 0x29C ((__int64)a1 + 0x29C) ---
    float    wh_cs_MinIdleTurnTimeout;              // 0x29C  // vtable+0x48

    // --- offset 0x2A0 (a1 + 0x54) ---
    float    wh_cs_MaxIdleTurnTimeout;              // 0x2A0  // vtable+0x48

    // --- offset 0x2A4 ((__int64)a1 + 0x2A4) ---
    float    wh_cs_IdleTurnPredictionTimeout;       // 0x2A4  // vtable+0x48

    // --- offset 0x2A8 (a1 + 0x55) ---
    float    wh_cs_IdleTurnInterruptionThreshold;   // 0x2A8  // vtable+0x48

    // --- offset 0x2AC ((__int64)a1 + 0x2AC) ---
    int32_t  wh_cs_DebugIdleTurns;                  // 0x2AC  // "Debug idle turns." (default=0, flags=2)

    // --- offset 0x2B0 (a1 + 0x56) ---
    int32_t  wh_cs_WeaponProcSolver;                // 0x2B0  // "Procedural weapon impact solver." (default=1, flags=2)

    // --- offset 0x2B4 ((__int64)a1 + 0x2B4) ---
    float    wh_cs_WeaponProcSolverRecoveryTime;    // 0x2B4  // vtable+0x48

    // --- offset 0x2B8 (a1 + 0x57) ---
    float    wh_cs_WeaponProcSolverRotRecoveryTimeMin; // 0x2B8 // vtable+0x48

    // --- offset 0x2BC ((__int64)a1 + 0x2BC) ---
    float    wh_cs_WeaponProcSolverRotRecoveryTimeMax; // 0x2BC // vtable+0x48

    // --- offset 0x2C0 (a1 + 0x58) ---
    float    wh_cs_WeaponProcSolverRecoveryIKBlendThreshold; // 0x2C0 // vtable+0x48

    // --- offset 0x2C4 ((__int64)a1 + 0x2C4) ---
    float    wh_cs_WeaponProcSolverRotSmoothTime;   // 0x2C4  // vtable+0x48

    // --- offset 0x2C8 (a1 + 0x59) ---
    float    wh_cs_WeaponProcSolverRotInterpolatorSel; // 0x2C8 // vtable+0x48

    // --- offset 0x2CC ((__int64)a1 + 0x2CC) ---
    float    wh_cs_WeaponProcSolverRotRecoverySharpness; // 0x2CC // vtable+0x48

    // --- offset 0x2D0 (a1 + 0x5A) ---
    float    wh_cs_WeaponProcSolverRotAnimDelaySharpness; // 0x2D0 // vtable+0x48

    // --- offset 0x2D4 ((__int64)a1 + 0x2D4) ---
    float    wh_cs_WeaponProcSolverRotMaxAnimDeviationAng; // 0x2D4 // vtable+0x48

    // --- offset 0x2D8 (a1 + 0x5B) ---
    float    wh_cs_WeaponProcSolverPosOffhandFade;  // 0x2D8  // vtable+0x48

    // --- offset 0x2DC ((__int64)a1 + 0x2DC) ---
    float    wh_cs_WeaponProcSolverImpactArea;      // 0x2DC  // vtable+0x48

    // --- offset 0x2E0 (a1 + 0x5C) ---
    float    wh_cs_WeaponProcSolverColExtraOffset;  // 0x2E0  // vtable+0x48

    // --- offset 0x2E4 ((__int64)a1 + 0x2E4) ---
    float    wh_cs_WeaponProcSolverColBlendLimiter; // 0x2E4  // vtable+0x48

    // --- offset 0x2E8 (a1 + 0x5D) ---
    float    wh_cs_WeaponProcSolverRecoilEffectDist; // 0x2E8 // vtable+0x48

    // --- offset 0x2EC ((__int64)a1 + 0x2EC) ---
    float    wh_cs_WeaponProcSolverRecoilEffectTime; // 0x2EC // vtable+0x48

    // --- offset 0x2F0 (a1 + 0x5E) ---
    int32_t  wh_cs_WeaponProcSolverDebug;           // 0x2F0  // "Enables debug draw for procedural weapon impact solver" (default=0, flags=2)

    // --- offset 0x2F4 ((__int64)a1 + 0x2F4) ---
    int32_t  wh_cs_WeaponProcSolverMethod;          // 0x2F4  // "Switches solver mode = 0 - 1. first collision, 2. continous" (default=1, flags=2)

    // --- offset 0x2F8 (a1 + 0x5F) ---
    float    wh_cs_WeaponProcSolverNearColDist;     // 0x2F8  // vtable+0x48

    // --- offset 0x2FC ((__int64)a1 + 0x2FC) ---
    float    wh_cs_WeaponProcSolverNearColDistVisualFilter; // 0x2FC // vtable+0x48

    // --- offset 0x300 (a1 + 0x60) ---
    float    wh_cs_WeaponProcSolverColFilterFOVOBias; // 0x300 // vtable+0x48

    // --- offset 0x304 ((__int64)a1 + 0x304) ---
    int32_t  wh_cs_WeaponProcSolverDebugCollisions; // 0x304  // "Procedural weapon impact solver- enables collision debug draw" (default=0, flags=2)

    // --- offset 0x308 (a1 + 0x61) ---
    float    wh_cs_UnarmedWeaponRadius;             // 0x308  // vtable+0x48

    // --- offset 0x30C ((__int64)a1 + 0x30C) ---
    float    wh_cs_WeaponCollisionCCDPosBias;       // 0x30C  // vtable+0x48

    // --- offset 0x310 (a1 + 0x62) ---
    int32_t  wh_cs_WeaponProcSolverProfiling;       // 0x310  // "Enables profiling of weapon solver." (default=0, flags=2)

    // --- offset 0x314 ((__int64)a1 + 0x314) ---
    int32_t  wh_cs_DBQueryProfiling;                // 0x314  // "Enables profiling of database queries." (default=0, flags=2)

    // --- offset 0x318 (a1 + 0x63) ---
    int32_t  wh_cs_DBQueryCache;                    // 0x318  // "Enables cache for database queries." (default=0, flags=2)

    // --- offset 0x31C ((__int64)a1 + 0x31C) ---
    float    wh_cs_WeaponProcSolverLod1Duration;    // 0x31C  // vtable+0x48

    // --- offset 0x320 (a1 + 0x64) ---
    int32_t  wh_cs_WeaponProcSolverForceLOD;        // 0x320  // "Forces LOD - 0 disabled, 1 limited colliding time, 2 no collision" (default=0, flags=2)

    // --- offset 0x324 ((__int64)a1 + 0x324) ---
    int32_t  wh_cs_WeaponProcDisableOffhand;        // 0x324  // "Forces disabled offhand for weapon solver" (default=1, flags=2)

    // --- offset 0x328 (a1 + 0x65) ---
    float    wh_cs_BehindCollisionIgnoreThreshold;  // 0x328  // vtable+0x48

    // --- offset 0x32C ((__int64)a1 + 0x32C) ---
    float    wh_cs_UniversalValue0;                 // 0x32C  // vtable+0x48

    // --- offset 0x330 (a1 + 0x66) ---
    float    wh_cs_UniversalValue1;                 // 0x330  // vtable+0x48

    // --- offset 0x334 ((__int64)a1 + 0x334) ---
    float    wh_cs_UniversalValue2;                 // 0x334  // vtable+0x48

    // --- offset 0x338 (a1 + 0x67) ---
    float    wh_cs_TimeAlignment_MaxBlockSpeedBias; // 0x338  // vtable+0x48

    // --- offset 0x33C ((__int64)a1 + 0x33C) ---
    float    wh_cs_TimeAlignment_MinBlockSpeedBias; // 0x33C  // vtable+0x48

    // --- offset 0x340 (a1 + 0x68) ---
    float    wh_cs_TimeAlignment_BlockSpeedMod;     // 0x340  // vtable+0x48

    // --- offset 0x344 ((__int64)a1 + 0x344) ---
    float    wh_cs_TimeAlignment_MaxAttackSpeedBias; // 0x344 // vtable+0x48

    // --- offset 0x348 (a1 + 0x69) ---
    float    wh_cs_TimeAlignment_MinAttackSpeedBias; // 0x348 // vtable+0x48  (note: name says "Min" but a1+0x69 = 0x348 vs 0x344 "Max")

    // --- offset 0x34C ((__int64)a1 + 0x34C) ---
    float    wh_cs_TimeAlignment_MaxAnimAddition;   // 0x34C  // vtable+0x48

    // --- offset 0x350 (a1 + 0x6A) ---
    float    wh_cs_TimeAlignment_MinConstSpeedBias; // 0x350  // vtable+0x48

    // --- offset 0x354 ((__int64)a1 + 0x354) ---
    float    wh_cs_TimeAlignment_ImpulseMinSpeed;   // 0x354  // vtable+0x48

    // --- offset 0x358 (a1 + 0x6B) ---
    float    wh_cs_TimeAlignment_SlotDelayDuration; // 0x358  // vtable+0x48

    // --- offset 0x35C ((__int64)a1 + 0x35C) ---
    int32_t  wh_cs_EnableStealthActions;            // 0x35C  // "Enables stealth actions" (default=1, flags=2)

    // --- offset 0x360 (a1 + 0x6C) ---
    int32_t  wh_cs_CombatCameraStyle;               // 0x360  // "Combat camera style [0]-Fixed at opponent, [1]-Dynamic" (default=1, flags=2)
                                                    //         NOTE: same QWORD index 0x6C as PlayerInputMouseUnlocking at 0x06C.
                                                    //         This is a second registration at a1+0x6C = 0x360, distinct from (__int64)a1+0x6C=0x06C.

    // --- offset 0x364 ((__int64)a1 + 0x364) ---
    int32_t  wh_cs_DisableCombatCamera;             // 0x364  // "Disables combat camera." (default=0, flags=2)

    // --- offset 0x368 (a1 + 0x6D) ---
    float    wh_cs_CombatAnimCameraSmooth;          // 0x368  // vtable+0x48

    // --- offset 0x36C ((__int64)a1 + 0x36C) ---
    float    wh_cs_CombatAnimCameraBlendOut;        // 0x36C  // vtable+0x48

    // --- offset 0x370 (a1 + 0x6E) ---
    float    wh_cs_Combat3PCameraFOV;               // 0x370  // vtable+0x48

    // --- offset 0x374 ((__int64)a1 + 0x374) ---
    int32_t  wh_cs_ShowLiveSpatialGrid;             // 0x374  // "Show runtime spatial grid for debugging." (default=0, flags=2)

    // --- offset 0x378 (a1 + 0x6F) ---
    int32_t  wh_cs_ShowPreprocessedSpatialGrid;     // 0x378  // "Show preprocessed spatial grid for debugging." (default=0, flags=2)

    // --- offset 0x37C ((__int64)a1 + 0x37C) ---
    float    wh_cs_SpatialGridBlendSpace;           // 0x37C  // vtable+0x48

    // --- offset 0x380 (a1 + 0x70) ---
    float    wh_cs_SpatialGridRadius;               // 0x380  // vtable+0x48

    // --- offset 0x384 ((__int64)a1 + 0x384) ---
    float    wh_cs_SpatialGridWeaponLength;         // 0x384  // vtable+0x48

    // --- offset 0x388 (a1 + 0x71) ---
    float    wh_cs_SpatialGridBlendSpaceDistance;   // 0x388  // vtable+0x48

    uint8_t  _pad_38C[0x4];                         // 0x38C

    // --- offset 0x390 (a1[0x72]) ---
    int64_t  pCVar_wh_cs_SpatialGridDisection;      // 0x390  // ICVar* "Spatial grid disections (333 or 332 etc)" (default="322")

    // --- offset 0x398 (a1 + 0x73) ---
    int32_t  wh_cs_ShowEnvSpatialGrid;              // 0x398  // "Enable visual debug of environment." (default=0, flags=4)

    // --- offset 0x39C ((__int64)a1 + 0x39C) ---
    float    wh_cs_EnvSpatialGridRefreshRate;       // 0x39C  // vtable+0x48

    // --- offset 0x3A0 (a1[0x74]) ---
    int64_t  pCVar_wh_cs_DebugObstacleTestTarget;   // 0x3A0  // ICVar* "Enables debug draw for obstacles test on given entity."

    // --- offset 0x3A8 (a1 + 0x75) ---
    int32_t  wh_cs_DebugObstacleMask;               // 0x3A8  // "Allow filter obstacle test to debug draw." (default=0, flags=2)

    // --- offset 0x3AC ((__int64)a1 + 0x3AC) ---
    int32_t  wh_cs_SpatialGridPreprocess;           // 0x3AC  // "Enables spatial analyzation during preprocessing." (default=1, flags=2)

    // --- offset 0x3B0 (a1 + 0x76) ---
    int32_t  wh_cs_EnableNavmeshTest;               // 0x3B0  // "Enables navmesh tests for some action types." (default=1, flags=2)

    // --- offset 0x3B4 ((__int64)a1 + 0x3B4) ---
    float    wh_cs_DisabledAttackTimeout;           // 0x3B4  // vtable+0x48

    // --- offset 0x3B8 (a1 + 0x77) ---
    int32_t  wh_cs_DisabledAttackDebug;             // 0x3B8  // "Forces interrupted attacks for debugging." (default=0, flags=2)

    // --- offset 0x3BC ((__int64)a1 + 0x3BC) ---
    float    wh_cs_ThreatenedTargetsSelectionDistance; // 0x3BC // vtable+0x48

    // --- offset 0x3C0 (a1 + 0x78) ---
    float    wh_cs_ThreatenedTargetsSelectionFOV;   // 0x3C0  // vtable+0x48

    uint8_t  _pad_3C4[0x4];                         // 0x3C4

    // --- offset 0x3C8 (a1[0x79]) ---
    int64_t  pCVar_wh_cs_DebugFilter;               // 0x3C8  // ICVar* "BASIC|MODEL|TIME_COP|..." (filter string)

    // --- offset 0x3D0 (a1 + 0x7A) ---
    int32_t  wh_cs_TraceMNDebug;                    // 0x3D0  // "Trace mn_debugs of all CA in combat to trace." (default=0, flags=2)

    // --- offset 0x3D4 ((__int64)a1 + 0x3D4) ---
    int32_t  wh_cs_ProcessSyncHits;                 // 0x3D4  // "Enabled update sync hits..." (default=0, flags=4)

    // --- offset 0x3D8 (a1[0x7B]) ---
    int64_t  pCVar_wh_cs_DebugIsAimedOn;            // 0x3D8  // ICVar* "Enables state IsAimed on given actor."

    // --- offset 0x3E0 (a1[0x7C]) ---
    int64_t  pCVar_wh_cs_DebugIsAimedOff;           // 0x3E0  // ICVar* "Disables state IsAimed on given actor."

    // --- offset 0x3E8 (a1 + 0x7D) ---
    int32_t  wh_cs_DebugDrawLods;                   // 0x3E8  // "Enables lod manager debug draw" (default=0, flags=4)

    // --- offset 0x3EC ((__int64)a1 + 0x3EC) ---
    int32_t  wh_cs_ForceLod;                        // 0x3EC  // vtable+0x48
                                                    //         UNVERIFIED type: name "ForceLod" could be int

    // --- offset 0x3F0 (a1 + 0x7E) ---
    float    wh_cs_LodNearDistance;                 // 0x3F0  // vtable+0x48

    // --- offset 0x3F4 ((__int64)a1 + 0x3F4) ---
    float    wh_cs_LodFarDistance;                  // 0x3F4  // vtable+0x48

    // --- offset 0x3F8 (a1 + 0x7F) ---
    float    wh_cs_LodAmbientDistance;              // 0x3F8  // vtable+0x48

    // --- offset 0x3FC ((__int64)a1 + 0x3FC) ---
    float    wh_cs_CursorOffsetNPC;                 // 0x3FC  // vtable+0x48

    // --- offset 0x400 (a1 + 0x80) ---
    float    wh_cs_CursorOffsetDog;                 // 0x400  // vtable+0x48

    // --- offset 0x404 ((__int64)a1 + 0x404) ---
    float    wh_cs_AutomationAction_DelayedEnd;     // 0x404  // vtable+0x48

    // --- offset 0x408 (a1 + 0x81) ---
    int32_t  wh_cs_AutomationAction_StaticPreblockEnabled; // 0x408 // "Combat automation - enables static preblock." (default=0, flags=2)

    // --- offset 0x40C ((__int64)a1 + 0x40C) ---
    float    wh_cs_AutomationAction_StaticPreblockUpdateInterval; // 0x40C // vtable+0x48

    // --- offset 0x410 (a1 + 0x82) ---
    float    wh_cs_AutomationAction_StaticPreblockRateHistoryDuration; // 0x410 // vtable+0x48

    // --- offset 0x414 ((__int64)a1 + 0x414) ---
    float    wh_cs_AutomationAction_AttackUpdateInterval; // 0x414 // vtable+0x48

    // --- offset 0x418 (a1 + 0x83) ---
    float    wh_cs_AutomationAction_HigherComboStepBias; // 0x418 // vtable+0x48

    // --- offset 0x41C ((__int64)a1 + 0x41C) ---
    float    wh_cs_AutomationAction_ZoneChangeToAttackMinDelay; // 0x41C // vtable+0x48

    // --- offset 0x420 (a1 + 0x84) ---
    float    wh_cs_AutomationAction_ZoneChangeUpdateInterval; // 0x420 // vtable+0x48

    // --- offset 0x424 ((__int64)a1 + 0x424) ---
    int32_t  wh_cs_AutomationAction_ZoneChangeSequenceMinCount; // 0x424 // "Combat automation - minimal sequence changes." (default=2, flags=2)

    // --- offset 0x428 (a1 + 0x85) ---
    int32_t  wh_cs_AutomationAction_ZoneChangeSequenceMaxCount; // 0x428 // "Combat automation - maximum sequence changes." (default=5, flags=2)

    // --- offset 0x42C ((__int64)a1 + 0x42C) ---
    int32_t  wh_cs_AutomationAction_ZoneChangeAttackSequenceMinCount; // 0x42C // "Combat automation - minimal preattack sequence changes." (default=1, flags=2)

    // --- offset 0x430 (a1 + 0x86) ---
    int32_t  wh_cs_AutomationAction_ZoneChangeAttackSequenceMaxCount; // 0x430 // "Combat automation - maximum preattack sequence changes." (default=3, flags=2)

    // --- offset 0x434 ((__int64)a1 + 0x434) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceMinTimeMin; // 0x434 // vtable+0x48

    // --- offset 0x438 (a1 + 0x87) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceMaxTimeMin; // 0x438 // vtable+0x48

    // --- offset 0x43C ((__int64)a1 + 0x43C) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceMinTimeMax; // 0x43C // vtable+0x48

    // --- offset 0x440 (a1 + 0x88) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceMaxTimeMax; // 0x440 // vtable+0x48

    // --- offset 0x444 ((__int64)a1 + 0x444) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceTime; // 0x444 // vtable+0x48

    // --- offset 0x448 (a1 + 0x89) ---
    float    wh_cs_AutomationAction_ZoneChangeSequenceChangeGap; // 0x448 // vtable+0x48

    // --- offset 0x44C ((__int64)a1 + 0x44C) ---
    int32_t  wh_cs_AutomationAction_ZoneChangeDebugDraw; // 0x44C // "Debug AI automation: Enables zone selection debug draw." (default=0, flags=2)

    // --- offset 0x450 (a1 + 0x8A) ---
    float    wh_cs_AutomationAction_ZoneChangeQualityTimingCoef; // 0x450 // vtable+0x48

    // --- offset 0x454 ((__int64)a1 + 0x454) ---
    int32_t  wh_cs_AutomationAction_GuardDebugDraw; // 0x454  // "Debug AI automation: Guard automation debug draw." (default=0, flags=2)

    // --- offset 0x458 (a1 + 0x8B) ---
    float    wh_cs_AutomationAction_GuardUpdateInterval; // 0x458 // vtable+0x48

    // --- offset 0x45C ((__int64)a1 + 0x45C) ---
    float    wh_cs_AutomationAction_GuardMaxSpeed;  // 0x45C  // vtable+0x48

    // --- offset 0x460 (a1 + 0x8C) ---
    float    wh_cs_AutomationAction_GuardMinAtkDist; // 0x460 // vtable+0x48

    // --- offset 0x464 ((__int64)a1 + 0x464) ---
    float    wh_cs_AutomationAction_GuardFOV;       // 0x464  // vtable+0x48

    // --- offset 0x468 (a1 + 0x8D) ---
    float    wh_cs_AutomationAction_GuardFOVVertical; // 0x468 // vtable+0x48

    // --- offset 0x46C ((__int64)a1 + 0x46C) ---
    float    wh_cs_AutomationAction_GuardFOVHyst;   // 0x46C  // vtable+0x48

    // --- offset 0x470 (a1 + 0x8E) ---
    float    wh_cs_AutomationAction_GuardEscapeMinDuration; // 0x470 // vtable+0x48

    // --- offset 0x474 ((__int64)a1 + 0x474) ---
    float    wh_cs_AutomationAction_ShoutIdleUpdateInterval; // 0x474 // vtable+0x48

    // --- offset 0x478 (a1 + 0x8F) ---
    float    wh_cs_AutomationAction_ShoutIdleGuardCooldown; // 0x478 // vtable+0x48

    // --- offset 0x47C ((__int64)a1 + 0x47C) ---
    float    wh_cs_AutomationAction_ShoutIdleGuardCooldownVariation; // 0x47C // vtable+0x48

    // --- offset 0x480 (a1 + 0x90) ---
    float    wh_cs_AutomationAction_ShoutActionGuardCooldown; // 0x480 // vtable+0x48

    // --- offset 0x484 ((__int64)a1 + 0x484) ---
    float    wh_cs_AutomationAction_ShoutActionGuardCooldownVariation; // 0x484 // vtable+0x48

    // --- offset 0x488 (a1 + 0x91) ---
    float    wh_cs_AutomationAction_ShoutClinchGuardCooldown; // 0x488 // vtable+0x48

    // --- offset 0x48C ((__int64)a1 + 0x48C) ---
    float    wh_cs_AutomationAction_ShoutDistanceLimitMax; // 0x48C // vtable+0x48

    // --- offset 0x490 (a1 + 0x92) ---
    float    wh_cs_AutomationAction_WeaponsUpdateInterval; // 0x490 // vtable+0x48

    // --- offset 0x494 ((__int64)a1 + 0x494) ---
    float    wh_cs_AutomationAction_WeaponOversizedAttackProblemDuration; // 0x494 // vtable+0x48

    // --- offset 0x498 (a1 + 0x93) ---
    float    wh_cs_AutomationAction_WeaponAttackDistTimeTolerance; // 0x498 // vtable+0x48

    // --- offset 0x49C ((__int64)a1 + 0x49C) ---
    float    wh_cs_AutomationAction_WeaponMissileInitRandCoef; // 0x49C // vtable+0x48

    // --- offset 0x4A0 (a1 + 0x94) ---
    int32_t  wh_cs_AutomationAction_WeaponUnreachedTest; // 0x4A0 // "Debug AI automation: Weapon automation - testing..." (default=0, flags=2)

    // --- offset 0x4A4 ((__int64)a1 + 0x4A4) ---
    int32_t  wh_cs_AutomationAction_DebugDraw;      // 0x4A4  // "Debug AI automation: Enables debug draw." (default=0, flags=2)

    // --- offset 0x4A8 (a1[0x95]) ---
    int64_t  pCVar_wh_cs_AutomationAction_DebugDrawTarget; // 0x4A8 // ICVar* "Enables debug automation on given entity."

    // --- offset 0x4B0 (a1 + 0x96) ---
    float    wh_cs_AutomationAction_MoveProblem_UnreachableFilterDuration; // 0x4B0 // vtable+0x48

    // --- offset 0x4B4 ((__int64)a1 + 0x4B4) ---
    float    wh_cs_AutomationAction_MoveProblem_EventFilteringTreshold; // 0x4B4 // vtable+0x48

    // --- offset 0x4B8 (a1 + 0x97) ---
    float    wh_cs_AutomationAction_MoveProblem_AfterHuntAttackDuration; // 0x4B8 // vtable+0x48

    // --- offset 0x4BC ((__int64)a1 + 0x4BC) ---
    float    wh_cs_AutomationAction_MoveProblem_WeaponChangeDuration; // 0x4BC // vtable+0x48

    // --- offset 0x4C0 (a1 + 0x98) ---
    float    wh_cs_AutomationAction_MoveProblem_UncertainDuration; // 0x4C0 // vtable+0x48

    // --- offset 0x4C4 ((__int64)a1 + 0x4C4) ---
    float    wh_cs_AutomationAction_MoveProblem_DistanceThreat; // 0x4C4 // vtable+0x48

    // --- offset 0x4C8 (a1 + 0x99) ---
    float    wh_cs_AutomationAction_MoveProblem_DistanceThreatForcedUncertain; // 0x4C8 // vtable+0x48

    // --- offset 0x4CC ((__int64)a1 + 0x4CC) ---
    float    wh_cs_AutomationAction_MoveProblem_DistanceFlee; // 0x4CC // vtable+0x48

    // --- offset 0x4D0 (a1 + 0x9A) ---
    float    wh_cs_AutomationAction_MoveProblem_UnreachedFilterDuration; // 0x4D0 // vtable+0x48

    // --- offset 0x4D4 ((__int64)a1 + 0x4D4) ---
    float    wh_cs_AutomationAction_MoveProblem_TotalDuration; // 0x4D4 // vtable+0x48

    // --- offset 0x4D8 (a1 + 0x9B) ---
    float    wh_cs_AutomationAction_MoveProblem_DebugForceUncertain; // 0x4D8 // vtable+0x48

    // --- offset 0x4DC ((__int64)a1 + 0x4DC) ---
    float    wh_cs_AutomationAction_MissileHuntAttackCooldown; // 0x4DC // vtable+0x48

    // --- offset 0x4E0 (a1 + 0x9C) ---
    float    wh_cs_AutomationAction_MoveProblem_BypassUncertainOnIsAimedDuration; // 0x4E0 // vtable+0x48

    // --- offset 0x4E4 ((__int64)a1 + 0x4E4) ---
    float    wh_cs_AutomationAction_HuntAttackDist; // 0x4E4  // vtable+0x48

    // --- offset 0x4E8 (a1 + 0x9D) ---
    float    wh_cs_AutomationAction_HuntAttackDistRand; // 0x4E8 // vtable+0x48

    // --- offset 0x4EC ((__int64)a1 + 0x4EC) ---
    float    wh_cs_AutomationAction_HuntAttackTimeLimit; // 0x4EC // vtable+0x48

    // --- offset 0x4F0 (a1 + 0x9E) ---
    float    wh_cs_AutomationAction_MissileUpdateInterval; // 0x4F0 // vtable+0x48

    // --- offset 0x4F4 ((__int64)a1 + 0x4F4) ---
    float    wh_cs_AutomationAction_MissileCylRaycastRadius; // 0x4F4 // vtable+0x48

    // --- offset 0x4F8 (a1 + 0x9F) ---
    int32_t  wh_cs_AutomationAction_MissileDebugDraw; // 0x4F8 // "AI automation: debug draw for missile automation." (default=0, flags=2)

    // --- offset 0x4FC ((__int64)a1 + 0x4FC) ---
    float    wh_cs_AutomationAction_DefenseMoveReactionVelocityLim; // 0x4FC // vtable+0x48

    // --- offset 0x500 (a1[0xA0]) ---
    int64_t  pCVar_wh_cs_Automation1_Target;        // 0x500  // ICVar* "Enables debug AI on given entity."

    // --- offset 0x508 (a1 + 0xA1) ---
    int32_t  wh_cs_Automation1_Mode;                // 0x508  // "Allows to specify which automation will be started..." (default=4, flags=2)

    // --- offset 0x50C ((__int64)a1 + 0x50C) ---
    float    wh_cs_Automation1_NoAction;            // 0x50C  // vtable+0x48

    // --- offset 0x510 (a1 + 0xA2) ---
    float    wh_cs_Automation1_NB;                  // 0x510  // vtable+0x48

    // --- offset 0x514 ((__int64)a1 + 0x514) ---
    float    wh_cs_Automation1_PB;                  // 0x514  // vtable+0x48

    // --- offset 0x518 (a1 + 0xA3) ---
    float    wh_cs_Automation1_SPB;                 // 0x518  // vtable+0x48

    // --- offset 0x51C ((__int64)a1 + 0x51C) ---
    float    wh_cs_Automation1_Dodge;               // 0x51C  // vtable+0x48

    // --- offset 0x520 (a1 + 0xA4) ---
    int32_t  wh_cs_Automation1_StaticPreblock;      // 0x520  // "Debug AI: enables static preblock" (default=-1, flags=2)

    // --- offset 0x524 ((__int64)a1 + 0x524) ---
    float    wh_cs_Automation1_ReactivePreblockProb; // 0x524 // vtable+0x48

    // --- offset 0x528 (a1 + 0xA5) ---
    float    wh_cs_Automation1_ReactivePreblockDelayMin; // 0x528 // vtable+0x48

    // --- offset 0x52C ((__int64)a1 + 0x52C) ---
    float    wh_cs_Automation1_ReactivePreblockDelayMax; // 0x52C // vtable+0x48

    // --- offset 0x530 (a1 + 0xA6) ---
    float    wh_cs_Automation1_TrickReactionDelayMin; // 0x530 // vtable+0x48

    // --- offset 0x534 ((__int64)a1 + 0x534) ---
    float    wh_cs_Automation1_TrickReactionDelayMax; // 0x534 // vtable+0x48

    // --- offset 0x538 (a1 + 0xA7) ---
    float    wh_cs_Automation1_PeriodicalAttackTime; // 0x538 // vtable+0x48

    // --- offset 0x53C ((__int64)a1 + 0x53C) ---
    float    wh_cs_Automation1_RiposteProb;         // 0x53C  // vtable+0x48

    // --- offset 0x540 (a1 + 0xA8) ---     NOTE: a1[0xA8] = 0x540
    float    wh_cs_Automation1_NoComboProb;         // 0x540  // vtable+0x48

    // --- offset 0x544 ((__int64)a1 + 0x544) ---
    float    wh_cs_Automation1_ComboProb;           // 0x544  // vtable+0x48

    // --- offset 0x548 (a1 + 0xA9) ---
    float    wh_cs_Automation1_NaturalComboProb;    // 0x548  // vtable+0x48

    // --- offset 0x54C ((__int64)a1 + 0x54C) ---
    float    wh_cs_Automation1_NaturalComboLightAttackProb; // 0x54C // vtable+0x48

    // --- offset 0x550 (a1 + 0xAA) ---
    float    wh_cs_Automation1_TrickEndAttackProb;  // 0x550  // vtable+0x48

    // --- offset 0x554 ((__int64)a1 + 0x554) ---
    float    wh_cs_Automation1_TrickAttackProb;     // 0x554  // vtable+0x48

    // --- offset 0x558 (a1 + 0xAB) ---
    float    wh_cs_Automation1_TrickChangeZoneProb; // 0x558  // vtable+0x48

    // --- offset 0x55C ((__int64)a1 + 0x55C) ---
    float    wh_cs_Automation1_TrickActionDelayMin; // 0x55C  // vtable+0x48

    // --- offset 0x560 (a1 + 0xAC) ---
    float    wh_cs_Automation1_TrickActionDelayMax; // 0x560  // vtable+0x48

    // --- offset 0x564 ((__int64)a1 + 0x564) ---
    float    wh_cs_Automation1_TrickNewQueryTimeoutMin; // 0x564 // vtable+0x48

    // --- offset 0x568 (a1 + 0xAD) ---
    float    wh_cs_Automation1_TrickNewQueryTimeoutMax; // 0x568 // vtable+0x48

    // --- offset 0x56C ((__int64)a1 + 0x56C) ---
    float    wh_cs_Automation1_ClinchActionDelayMin; // 0x56C // vtable+0x48

    // --- offset 0x570 (a1 + 0xAE) ---
    float    wh_cs_Automation1_ClinchActionDelayMax; // 0x570 // vtable+0x48

    // --- offset 0x574 ((__int64)a1 + 0x574) ---
    float    wh_cs_Automation1_GuardBorderLevel0;   // 0x574  // vtable+0x48

    // --- offset 0x578 (a1 + 0xAF) ---
    float    wh_cs_Automation1_GuardBorderLevel1;   // 0x578  // vtable+0x48

    // --- offset 0x57C ((__int64)a1 + 0x57C) ---
    float    wh_cs_Automation1_GuardAbilityLevel;   // 0x57C  // vtable+0x48

    // --- offset 0x580 (a1 + 0xB0) ---
    float    wh_cs_Automation1_GuardBorderHystDiameter; // 0x580 // vtable+0x48

    // --- offset 0x584 ((__int64)a1 + 0x584) ---
    float    wh_cs_Automation1_OpponentZoneAdaptationDelayMin; // 0x584 // vtable+0x48

    // --- offset 0x588 (a1 + 0xB1) ---
    float    wh_cs_Automation1_OpponentZoneAdaptationDelayMax; // 0x588 // vtable+0x48

    // --- offset 0x58C ((__int64)a1 + 0x58C) ---
    float    wh_cs_Automation1_ZoneChangeTimeoutMin; // 0x58C // vtable+0x48

    // --- offset 0x590 (a1 + 0xB2) ---
    float    wh_cs_Automation1_ZoneChangeTimeoutMax; // 0x590 // vtable+0x48

    // --- offset 0x594 ((__int64)a1 + 0x594) ---
    float    wh_cs_Automation1_StanceZoneSyncTimeoutMin; // 0x594 // vtable+0x48

    // --- offset 0x598 (a1 + 0xB3) ---
    float    wh_cs_Automation1_StanceZoneSyncTimeoutMax; // 0x598 // vtable+0x48

    // --- offset 0x59C ((__int64)a1 + 0x59C) ---
    int32_t  wh_cs_Automation1_ZoneSelectionMode;   // 0x59C  // "Forces zone selection mode - -1-RPG, 0-defense, 1-offense, 2-visual." (default=-1, flags=2)

    // --- offset 0x5A0 (a1 + 0xB4) ---
    float    wh_cs_Automation1_ZoneChangeOffenseModeWeight; // 0x5A0 // vtable+0x48

    // --- offset 0x5A4 ((__int64)a1 + 0x5A4) ---
    float    wh_cs_Automation1_ZoneChangeDefenseModeWeight; // 0x5A4 // vtable+0x48

    // --- offset 0x5A8 (a1 + 0xB5) ---
    float    wh_cs_Automation1_ZoneChangeTiredness; // 0x5A8  // vtable+0x48

    // --- offset 0x5AC ((__int64)a1 + 0x5AC) ---
    float    wh_cs_Automation1_WeaponMissileDistRangeMin; // 0x5AC // vtable+0x48

    // --- offset 0x5B0 (a1[0xB6]) ---
    int64_t  pCVar_wh_cs_Automation2_Target;        // 0x5B0  // ICVar* "Enables debug AI on given entity."

    // --- offset 0x5B8 (a1 + 0xB7) ---
    int32_t  wh_cs_Automation2_Mode;                // 0x5B8  // "Allows to specify which automation will be started..." (default=4, flags=2)

    // --- offset 0x5BC ((__int64)a1 + 0x5BC) ---
    float    wh_cs_Automation2_NoAction;            // 0x5BC  // vtable+0x48

    // --- offset 0x5C0 (a1 + 0xB8) ---
    float    wh_cs_Automation2_NB;                  // 0x5C0  // vtable+0x48

    // --- offset 0x5C4 ((__int64)a1 + 0x5C4) ---
    float    wh_cs_Automation2_PB;                  // 0x5C4  // vtable+0x48

    // --- offset 0x5C8 (a1 + 0xB9) ---
    float    wh_cs_Automation2_SPB;                 // 0x5C8  // vtable+0x48

    // --- offset 0x5CC ((__int64)a1 + 0x5CC) ---
    float    wh_cs_Automation2_Dodge;               // 0x5CC  // vtable+0x48

    // --- offset 0x5D0 (a1 + 0xBA) ---
    int32_t  wh_cs_Automation2_StaticPreblock;      // 0x5D0  // "Debug AI: enables static preblock" (default=-1, flags=2)

    // --- offset 0x5D4 ((__int64)a1 + 0x5D4) ---
    float    wh_cs_Automation2_ReactivePreblockProb; // 0x5D4 // vtable+0x48

    // --- offset 0x5D8 (a1 + 0xBB) ---
    float    wh_cs_Automation2_ReactivePreblockDelayMin; // 0x5D8 // vtable+0x48

    // --- offset 0x5DC ((__int64)a1 + 0x5DC) ---
    float    wh_cs_Automation2_ReactivePreblockDelayMax; // 0x5DC // vtable+0x48

    // --- offset 0x5E0 (a1 + 0xBC) ---
    float    wh_cs_Automation2_TrickReactionDelayMin; // 0x5E0 // vtable+0x48

    // --- offset 0x5E4 ((__int64)a1 + 0x5E4) ---
    float    wh_cs_Automation2_TrickReactionDelayMax; // 0x5E4 // vtable+0x48

    // --- offset 0x5E8 (a1 + 0xBD) ---
    float    wh_cs_Automation2_PeriodicalAttackTime; // 0x5E8 // vtable+0x48

    // --- offset 0x5EC ((__int64)a1 + 0x5EC) ---
    float    wh_cs_Automation2_RiposteProb;         // 0x5EC  // vtable+0x48

    // --- offset 0x5F0 (a1 + 0xBE) ---  NOTE: a1[0xBE] but Automation2 sequence continues from a1[0xBD]
    float    wh_cs_Automation2_NoComboProb;         // 0x5F0  // vtable+0x48

    // --- offset 0x5F4 ((__int64)a1 + 0x5F4) ---
    float    wh_cs_Automation2_ComboProb;           // 0x5F4  // vtable+0x48

    // --- offset 0x5F8 (a1 + 0xBF) ---
    float    wh_cs_Automation2_NaturalComboProb;    // 0x5F8  // vtable+0x48

    // --- offset 0x5FC ((__int64)a1 + 0x5FC) ---
    float    wh_cs_Automation2_NaturalComboLightAttackProb; // 0x5FC // vtable+0x48

    // --- offset 0x600 (a1 + 0xC0) ---
    float    wh_cs_Automation2_TrickEndAttackProb;  // 0x600  // vtable+0x48

    // --- offset 0x604 ((__int64)a1 + 0x604) ---
    float    wh_cs_Automation2_TrickAttackProb;     // 0x604  // vtable+0x48

    // --- offset 0x608 (a1 + 0xC1) ---
    float    wh_cs_Automation2_TrickChangeZoneProb; // 0x608  // vtable+0x48

    // --- offset 0x60C ((__int64)a1 + 0x60C) ---
    float    wh_cs_Automation2_TrickActionDelayMin; // 0x60C  // vtable+0x48

    // --- offset 0x610 (a1 + 0xC2) ---
    float    wh_cs_Automation2_TrickActionDelayMax; // 0x610  // vtable+0x48

    // --- offset 0x614 ((__int64)a1 + 0x614) ---
    float    wh_cs_Automation2_TrickNewQueryTimeoutMin; // 0x614 // vtable+0x48

    // --- offset 0x618 (a1 + 0xC3) ---
    float    wh_cs_Automation2_TrickNewQueryTimeoutMax; // 0x618 // vtable+0x48

    // --- offset 0x61C ((__int64)a1 + 0x61C) ---
    float    wh_cs_Automation2_ClinchActionDelayMin; // 0x61C // vtable+0x48

    // --- offset 0x620 (a1 + 0xC4) ---
    float    wh_cs_Automation2_ClinchActionDelayMax; // 0x620 // vtable+0x48

    // --- offset 0x624 ((__int64)a1 + 0x624) ---
    float    wh_cs_Automation2_GuardBorderLevel0;   // 0x624  // vtable+0x48

    // --- offset 0x628 (a1 + 0xC5) ---
    float    wh_cs_Automation2_GuardBorderLevel1;   // 0x628  // vtable+0x48

    // --- offset 0x62C ((__int64)a1 + 0x62C) ---
    float    wh_cs_Automation2_GuardAbilityLevel;   // 0x62C  // vtable+0x48

    // --- offset 0x630 (a1 + 0xC6) ---
    float    wh_cs_Automation2_GuardBorderHystDiameter; // 0x630 // vtable+0x48

    // --- offset 0x634 ((__int64)a1 + 0x634) ---
    float    wh_cs_Automation2_OpponentZoneAdaptationDelayMin; // 0x634 // vtable+0x48

    // --- offset 0x638 (a1 + 0xC7) ---
    float    wh_cs_Automation2_OpponentZoneAdaptationDelayMax; // 0x638 // vtable+0x48

    // --- offset 0x63C ((__int64)a1 + 0x63C) ---
    float    wh_cs_Automation2_ZoneChangeTimeoutMin; // 0x63C // vtable+0x48

    // --- offset 0x640 (a1 + 0xC8) ---
    float    wh_cs_Automation2_ZoneChangeTimeoutMax; // 0x640 // vtable+0x48

    // --- offset 0x644 ((__int64)a1 + 0x644) ---
    float    wh_cs_Automation2_StanceZoneSyncTimeoutMin; // 0x644 // vtable+0x48

    // --- offset 0x648 (a1 + 0xC9) ---
    float    wh_cs_Automation2_StanceZoneSyncTimeoutMax; // 0x648 // vtable+0x48

    // --- offset 0x64C ---
    // Note: a1[0xCA] = a1 + 0xCA = 0x650, but (__int64)a1+0x644 ended at 0x648.
    // Actually a1[0xC9] = 0x648, next is a1[0xCA] = 0x650. Gap at 0x64C.
    uint8_t  _pad_64C[0x4];                         // 0x64C
                                                    // UNVERIFIED: possible Automation2_ZoneSelectionMode here (not seen in decompilation)

    // --- offset 0x650 (a1 + 0xCA) ---
    float    wh_cs_Automation2_ZoneChangeOffenseModeWeight; // 0x650 // vtable+0x48

    // --- offset 0x654 ((__int64)a1 + 0x654) ---
    float    wh_cs_Automation2_ZoneChangeDefenseModeWeight; // 0x654 // vtable+0x48

    // --- offset 0x658 (a1 + 0xCB) ---
    float    wh_cs_Automation2_ZoneChangeTiredness; // 0x658  // vtable+0x48

    // --- offset 0x65C ((__int64)a1 + 0x65C) ---
    float    wh_cs_Automation2_WeaponMissileDistRangeMin; // 0x65C // vtable+0x48
    // last known field ends at 0x660

    static S_CombatSettings* GetInstance();           // Offsets.cpp
};
#pragma pack(pop)

static_assert(sizeof(S_CombatSettings) == 0x660, "Size mismatch for S_CombatSettings");

}  // namespace wh::combatmodule
