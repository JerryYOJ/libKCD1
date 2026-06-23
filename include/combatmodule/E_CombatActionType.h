#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// E_CombatActionType — combat action-type id.
//
// VERIFIED from combat_action_type.xml (Tables.pak): fixed table ids. These are
// the values returned by C_CombatActionTypeData / a combat action's data-row
// GetActionTypeId(), and the values held by the runtime globals
// (Offsets::ActionTypeId, e.g. ComboAttack()=0x18359B3B4).
//
// Runtime global == data-row id == XML id: C_CombatActionTypeDatabase::Init
// (sub_18071C6E4) uses the same per-row onLoad resolver pattern as the input-class
// DB (see E_CombatInputClass.h), and this is runtime-observed — the hunt-attack
// detection compares `dataRow->GetActionTypeId() == g_actionType_huntAttackSlave`
// and that equality holds, which is only possible if global == data-row id.
//
// NOTE for runtime comparisons: prefer the Offsets::ActionTypeId accessors (they
// read the live globals and are correct by construction even if the table ever
// changes). This enum is for typing/readability of data-row id fields.
// ---------------------------------------------------------------------------
enum class E_CombatActionType : int32_t {
    Invalid                       = -1,

    HitMovement                   = 0,
    BlockMoveBack                 = 1,
    BlockStepBack                 = 2,
    Attack                        = 3,
    Leap                          = 4,
    Movement                      = 5,
    Block                         = 6,
    HitTorso                      = 7,
    HitBlockBroken                = 8,
    HitBlockWeapon                = 9,
    GuardIdleUpperBody            = 10,
    GuardPreBlock                 = 11,
    GuardAttackStart              = 12,
    // 13: not present in the table
    PerfectBlock                  = 14,
    FailedAttackOnPB              = 15,
    SyncAttack                    = 16,
    SyncHit                       = 17,
    ComboAttack                   = 18,
    ComboHit                      = 19,
    GuardSyncMovementMaster       = 20,
    GuardSyncMovementSlave        = 21,
    // 22: not present in the table
    SyncPerfectBlock              = 23,
    SyncPerfectBlockHit           = 24,
    PerfectBlockDodge             = 25,
    FreeAttack                    = 26,
    FailedAttackOnBlock           = 27,
    StealthAttackSuccess          = 28,
    StealthAttackFail             = 29,
    StealthHitSuccess             = 30,
    StealthHitFail                = 31,
    RipostePerfectBlock           = 32,
    SyncTransitionMaster          = 33,
    SyncTransitionSlave           = 34,
    GuardStartSyncMovementMaster  = 35,
    GuardStartSyncMovementSlave   = 36,
    FreeRiderAttackStatic         = 37,
    FreeRiderAttack               = 38,
    RiderGuardIdle                = 39,
    RiderGuardMovement            = 40,
    RiderGuardJumpStart           = 41,
    RiderGuardJump                = 42,
    RiderGuardJumpEnd             = 43,
    RiderGuardMove2Idle           = 44,
    RiderGuardIdle2Move           = 45,
    RiderGuardRear                = 46,
    RiderGuardFastStop            = 47,
    HorsePullDownAttackSuccess    = 48,
    HorsePullDownHitSuccess       = 49,
    MercyAttack                   = 50,
    HuntAttackMaster              = 51,
    HuntAttackSlave               = 52,
    SyncDodge                     = 53,
    SyncDodgeHit                  = 54,
    SyncRiposte                   = 55,
    SyncRiposteHit                = 56,
    PerfectNormalBlock            = 57,

    // Group action types (broad-phase buckets).
    GroupFreeAttack               = 1000,
    GroupRiderAttack              = 1001,
    GroupPerfectBlock             = 1002,
    GroupStaticAttack             = 1003,
    GroupMeleeAttack              = 1004,
    GroupRiderMovement            = 1005,
    GroupAttack                   = 1006,
    GroupBlock                    = 1007,
    GroupHit                      = 1008,
    GroupSyncPerfectBlock         = 1009,
};

}  // namespace wh::combatmodule
