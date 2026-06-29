#include "Offsets/Offsets.h"
#include "framework/WuidRegistries.h"

uintptr_t Offsets::GetBase() {
    return REL::Module::get().base();
}

Offsets::IGameFramework* Offsets::GetCCryAction() {
    // 0x3785D88: global holding the IGameFramework* (CCryAction)
    static REL::Relocation<IGameFramework**> p{ REL::ID(882) };
    return *p;
}

// gEnv.p3DEngine (+0x08) is null in KCD; the live engine is the Cry3DEngineBase
// static C3DEngine* (qword_183785BC0), set in the C3DEngine ctor.
Offsets::I3DEngine* Offsets::Get3DEngine() {
    // 0x3785BC0: Cry3DEngineBase static C3DEngine*
    static REL::Relocation<I3DEngine**> p{ REL::ID(881) };
    return *p;
}

// CryEngine bucket allocator (the candidate std::vector's heap path). Matched pair.
void* Offsets::CryMemAlloc(std::size_t size) {
    // 0x28C040: sub_18028C040 CryEngine bucket pool malloc
    static REL::Relocation<void* (__fastcall*)(uint64_t)> f{ REL::ID(9) };
    return f(size);
}
void Offsets::CryMemFree(void* p, std::size_t size) {
    // 0x5B72C0: CryEngine::MemFree(ptr, size) (SIZED)
    static REL::Relocation<void (__fastcall*)(void*, uint64_t)> f{ REL::ID(25) };
    f(p, size);
}

// Central WUID->C_AIObject* map: the global qword_1837999E0 holds a pointer to the heap map.
namespace wh { namespace framework {
C_WuidObjectMap* GetWuidObjectMap() {
    // 0x37999E0: qword holds a POINTER to the heap std::unordered_map
    static REL::Relocation<C_WuidObjectMap**> p{ REL::ID(886) };
    return *p;
}

// container WUID -> its single C_Inventory (engine sub_1815F457C; its first arg is unused).
entitymodule::C_Inventory* GetInventoryForWuid(WUID w) {
    // 0x15F457C: sub_1815F457C(unused, &out, &wuid)
    void* out = nullptr;
    static REL::Relocation<void (__fastcall*)(const void*, void**, const WUID*)> f{ REL::ID(48) };
    f(nullptr, &out, &w);
    return reinterpret_cast<entitymodule::C_Inventory*>(out);
}
}}  // namespace wh::framework

// Combat action-type IDs: contiguous int32 array at RVA 0x359B330 (resolve the array
// object via REL::ID, then index — the per-element addresses are not object starts).
#define ACTION_TYPE_GETTER(Name, Index) \
    int32_t Offsets::ActionTypeId::Name() { \
        static REL::Relocation<int32_t*> arr{ REL::ID(875) }; \
        return arr.get()[Index]; \
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

// Combat input-class IDs: contiguous int32 array at RVA 0x359C2F0.
#define INPUT_CLASS_GETTER(Name, Index) \
    int32_t Offsets::InputClassId::Name() { \
        static REL::Relocation<int32_t*> arr{ REL::ID(876) }; \
        return arr.get()[Index]; \
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
