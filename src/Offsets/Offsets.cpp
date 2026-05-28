#include <Windows.h>
#include "Offsets/Offsets.h"

uintptr_t Offsets::GetBase() {
    static uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA("WHGame.DLL"));
    return base;
}

Offsets::IGameFramework* Offsets::GetCCryAction() {
    return *reinterpret_cast<IGameFramework**>(GetBase() + kCCryActionOffset);
}

#define ACTION_TYPE_GETTER(Name, Index) \
    int32_t Offsets::ActionTypeId::Name() { \
        return *reinterpret_cast<int32_t*>(GetBase() + kActionTypeIdBase + (Index) * sizeof(int32_t)); \
    }

ACTION_TYPE_GETTER(Attack,                      0)
ACTION_TYPE_GETTER(FreeAttack,                  1)
ACTION_TYPE_GETTER(Leap,                        2)
ACTION_TYPE_GETTER(MercyAttack,                 3)
ACTION_TYPE_GETTER(Block,                       4)
ACTION_TYPE_GETTER(BlockMoveBack,               5)
ACTION_TYPE_GETTER(BlockStepBack,               6)
ACTION_TYPE_GETTER(PerfectBlock,                7)
ACTION_TYPE_GETTER(PerfectNormalBlock,           8)
ACTION_TYPE_GETTER(RipostePerfectBlock,          9)
ACTION_TYPE_GETTER(PerfectBlockDodge,            10)
ACTION_TYPE_GETTER(SyncPerfectBlock,             11)
ACTION_TYPE_GETTER(SyncPerfectBlockHit,          12)
ACTION_TYPE_GETTER(SyncDodge,                    13)
ACTION_TYPE_GETTER(SyncDodgeHit,                 14)
ACTION_TYPE_GETTER(SyncRiposte,                  15)
ACTION_TYPE_GETTER(SyncRiposteHit,               16)
ACTION_TYPE_GETTER(HitTorso,                     17)
ACTION_TYPE_GETTER(HitBlockBroken,               18)
ACTION_TYPE_GETTER(HitBlockWeapon,               19)
ACTION_TYPE_GETTER(HitMovement,                  20)
ACTION_TYPE_GETTER(GuardIdleUpperBody,            21)
ACTION_TYPE_GETTER(GuardSyncMovementMaster,       22)
ACTION_TYPE_GETTER(GuardSyncMovementSlave,        23)
ACTION_TYPE_GETTER(GuardStartSyncMovementMaster,  24)
ACTION_TYPE_GETTER(GuardStartSyncMovementSlave,   25)
ACTION_TYPE_GETTER(Movement,                     26)
ACTION_TYPE_GETTER(GuardPreBlock,                27)
ACTION_TYPE_GETTER(GuardAttackStart,             28)
ACTION_TYPE_GETTER(FailedAttackOnBlock,           29)
ACTION_TYPE_GETTER(FailedAttackOnPB,              30)
ACTION_TYPE_GETTER(SyncAttack,                   31)
ACTION_TYPE_GETTER(SyncHit,                      32)
ACTION_TYPE_GETTER(ComboAttack,                  33)
ACTION_TYPE_GETTER(ComboHit,                     34)
ACTION_TYPE_GETTER(StealthAttackSuccess,          35)
ACTION_TYPE_GETTER(StealthAttackFail,             36)
ACTION_TYPE_GETTER(StealthHitSuccess,             37)
ACTION_TYPE_GETTER(StealthHitFail,               38)
ACTION_TYPE_GETTER(SyncTransitionMaster,          39)
ACTION_TYPE_GETTER(SyncTransitionSlave,           40)
ACTION_TYPE_GETTER(HuntAttackMaster,             41)
ACTION_TYPE_GETTER(HuntAttackSlave,              42)

#undef ACTION_TYPE_GETTER

#define INPUT_CLASS_GETTER(Name, Index) \
    int32_t Offsets::InputClassId::Name() { \
        return *reinterpret_cast<int32_t*>(GetBase() + kInputClassIdBase + (Index) * sizeof(int32_t)); \
    }

INPUT_CLASS_GETTER(AttackLight,     0)
INPUT_CLASS_GETTER(AttackHeavy,     1)
INPUT_CLASS_GETTER(AttackSpecial,   2)
INPUT_CLASS_GETTER(MoveLeft,        3)
INPUT_CLASS_GETTER(MoveRight,       4)
INPUT_CLASS_GETTER(MoveBack,        5)
INPUT_CLASS_GETTER(MoveForward,     6)
INPUT_CLASS_GETTER(Block,           7)

#undef INPUT_CLASS_GETTER
