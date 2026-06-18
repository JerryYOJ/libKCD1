// Compile this file to verify all static_assert(sizeof(...)) in the RE headers.
// Open RE/.build/ in Visual Studio via CMake and build — any size mismatch
// will be a compile error.

#include "CryEngine/CryCommon/BaseTypes.h"   // uint64 etc. needed by CryGUID.h

// ---- boost::container::vector layout probe ----
// The game's sorted containers (faction maps, info-manager holder index) are
// boost::container::vector (count-based {ptr, size, capacity}). Verify vcpkg's boost
// reproduces the shipped layout: 0x18, with m_start@0 / m_size@8 / m_capacity@0x10.
#include <boost/container/vector.hpp>
static_assert(sizeof(boost::container::vector<void*>) == 0x18,
              "boost::container::vector must be {ptr,size,cap} == 0x18 to match the binary");

// ---- The game's hash containers ARE MSVC std::unordered_map/set (0x40 _Hash, verified in IDA +
//      STL source). The old C_HashMap/C_Set replicas were removed; callers use the real std types.
//      This guard pins that the toolchain still produces the game's 0x40 layout. ----
#include <unordered_map>
#include <unordered_set>
static_assert(sizeof(std::unordered_map<unsigned long long, void*>) == 0x40, "std::unordered_map must match the game's 0x40 _Hash");
static_assert(sizeof(std::unordered_set<void*>) == 0x40, "std::unordered_set must match the game's 0x40 _Hash");
// SDK CryArray.h DynArray (SmallDynStorage). SmallDynStorage has only m_aElems (8 bytes)
// plus two EMPTY bases (RawStorage<T> + AllocPrefix); MSVC won't collapse multiple empty
// bases without __declspec(empty_bases), which bloats it to 16. We patched SmallDynStorage
// with __declspec(empty_bases) in CryArray.h so it matches the retail 8-byte single-pointer
// layout -- these guards confirm the patch:
#include "CryEngine/CryCommon/CryArray.h"
static_assert(sizeof(DynArray<int>)   == 0x8, "patched SmallDynStorage DynArray<int> must be 8 bytes");
static_assert(sizeof(DynArray<void*>) == 0x8, "patched SmallDynStorage DynArray<void*> must be 8 bytes");

// ---- stateful inline-pool allocator probe: a non-empty allocator (one Pool* member) must
//      make std::vector 0x20 ({alloc,begin,end,cap}) -- the shape of C_Faction's pool vectors.
#include <vector>
#include "framework/C_InlinePoolAllocator.h"
namespace { struct _AllocProbePool; }
static_assert(sizeof(std::vector<int, wh::framework::C_InlinePoolAllocator<int, _AllocProbePool>>) == 0x20,
              "stateful inline-pool allocator must make std::vector 0x20 (alloc ptr + begin/end/cap)");

#include "rpgmodule/C_Soul.h"                // pulls in most rpgmodule headers
#include "rpgmodule/C_RPGModule.h"
#include "rpgmodule/C_Effect.h"
#include "rpgmodule/S_RpgParams.h"
#include "rpgmodule/S_PerkPointCounters.h"
#include "crysystem/CXConsole.h"
#include "crysystem/CLog.h"
#include "crysystem/CScriptSystem.h"
#include "framework/I_Action.h"
#include "framework/I_ActionImpl.h"
#include "framework/C_BaseModule.h"
#include "framework/WuidRegistries.h"
#include "framework/C_ReadinessObserver.h"
#include "framework/I_ReadinessTask.h"
#include "framework/C_CrySaveGameHelper.h"
#include "framework/C_CryLoadGameHelper.h"
#include "framework/C_PlayerProfileWHManager.h"
#include "framework/C_SaveGameManager.h"
#include "game/S_GameContext.h"
#include "animationmodule/C_AnimationDatabase.h"
#include "animationmodule/I_SceneListener.h"
#include "entitymodule/I_ItemAttachmentListener.h"
#include "entitymodule/C_Item.h"
#include "entitymodule/S_ItemData.h"
#include "entitymodule/C_ItemRuntimeData.h"
#include "entitymodule/C_Inventory.h"
#include "entitymodule/C_EquipmentManager.h"
#include "combatmodule/I_CombatActor.h"
#include "combatmodule/I_CombatActorAction.h"
#include "combatmodule/C_CombatComboData.h"
#include "combatmodule/C_CombatDatabase.h"
#include "combatmodule/C_CombatModule.h"
#include "combatmodule/C_CombatScene.h"
#include "combatmodule/C_CombatActor.h"
#include "framework/C_ActionDirector.h"
#include "combatmodule/C_CombatActorDirector.h"
#include "combatmodule/I_CombatTarget.h"
#include "combatmodule/S_CombatActorState.h"
#include "combatmodule/C_CombatActorObject.h"
#include "combatmodule/C_CombatActorUpdatedObject.h"
#include "combatmodule/C_CombatTrigger.h"
#include "combatmodule/C_CombatSlotTrigger.h"
#include "combatmodule/C_CombatTriggerCombo.h"
#include "combatmodule/C_CombatTriggerPerfectBlock.h"
#include "combatmodule/C_CombatTriggerRiposte.h"
#include "combatmodule/C_CombatTriggerSyncPerfectBlock.h"
#include "combatmodule/C_CombatTriggerSyncRiposte.h"
#include "combatmodule/C_CombatTriggerSyncDodge.h"
#include "combatmodule/C_CombatComboManager.h"
#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/C_CombatActorActionManager.h"
#include "combatmodule/C_CombatActorHuntAttack.h"
#include "combatmodule/C_CombatActorHorsePullDown.h"
#include "combatmodule/C_CombatActorMercyKill.h"
#include "combatmodule/C_CombatActorActionT.h"
#include "combatmodule/S_CombatActorActionAttackParams.h"
#include "combatmodule/S_CombatActorActionStaticAttackParams.h"
#include "combatmodule/S_CombatActorActionSyncAttackParams.h"
#include "combatmodule/S_CombatActorActionBlockParams.h"
#include "combatmodule/S_CombatActorActionPerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionComposedRipostePerfectBlockParams.h"
#include "combatmodule/S_CombatActorActionHitParams.h"
#include "combatmodule/S_CombatActorActionFreeBlockParams.h"
#include "combatmodule/S_CombatActorActionBlockTriggerParams.h"
#include "combatmodule/S_CombatActorActionGuardParams.h"
#include "combatmodule/S_CombatActorActionGuardMovementParams.h"
#include "combatmodule/S_CombatActorActionGuardSyncMovementParams.h"
#include "combatmodule/S_CombatActorActionSyncHitParams.h"
#include "combatmodule/S_CombatActorActionSyncPerfectBlockHitParams.h"
#include "combatmodule/S_CombatActorActionSyncTransitionParams.h"
#include "combatmodule/S_CombatActorActionPoseModifierParams.h"
#include "combatmodule/C_CombatActionHelper.h"
#include "combatmodule/I_CombatActorActionBlock.h"
#include "combatmodule/I_CombatActionHelperOwner.h"
#include "combatmodule/C_CombatActorActionAttack.h"
#include "combatmodule/C_CombatActorActionStaticAttack.h"
#include "combatmodule/C_CombatActorActionSyncAttack.h"
#include "combatmodule/C_CombatActorActionBlock.h"
#include "combatmodule/C_CombatActorActionBlockTrigger.h"
#include "combatmodule/C_CombatActorActionFreeBlock.h"
#include "combatmodule/C_CombatActorActionPerfectBlock.h"
#include "combatmodule/C_CombatActorActionComposedRipostePerfectBlock.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlock.h"
#include "combatmodule/C_CombatActorActionSyncPerfectBlockHit.h"
#include "combatmodule/C_CombatActorActionHit.h"
#include "combatmodule/C_CombatActorActionSyncHit.h"
#include "combatmodule/C_CombatActorActionSyncTransition.h"
#include "combatmodule/C_CombatActorActionGuard.h"
#include "combatmodule/C_CombatActorActionGuardMovement.h"
#include "combatmodule/C_CombatActorActionGuardSyncMovement.h"
#include "combatmodule/C_CombatActorActionRiderMovement.h"
#include "combatmodule/C_CombatActorActionPoseModifier.h"
#include "combatmodule/S_CombatSettings.h"
#include "entitymodule/C_Player.h"
#include "Offsets/vtables/IGameObject.h"
#include "Offsets/vtables/IActorSystem.h"
#include "Offsets/vtables/IEntitySystemSink.h"
#include "Offsets/vtables/IEntityEventListener.h"
#include "xgenaimodule/BehaviorTree/I_Node.h"
#include "xgenaimodule/BehaviorTree/I_DebugNode.h"
#include "xgenaimodule/BehaviorTree/C_Node.h"
#include "xgenaimodule/BehaviorTree/C_Decorator.h"
#include "xgenaimodule/BehaviorTree/C_Composite.h"
#include "xgenaimodule/BehaviorTree/C_Composites.h"
#include "xgenaimodule/BehaviorTree/C_Gate.h"
#include "xgenaimodule/BehaviorTree/C_NodeWrapper.h"
#include "xgenaimodule/BehaviorTree/C_NodeContext.h"
#include "xgenaimodule/BehaviorTree/C_Barrier.h"
#include "xgenaimodule/BehaviorTree/bt/C_RemoveItem.h"
#include "xgenaimodule/BehaviorTree/bt/C_AddBuff.h"
#include "xgenaimodule/BehaviorTree/bt/C_VarOperation.h"
#include "rpgmodule/buff/C_BuffInstanceBase.h"
#include "rpgmodule/buff/C_SoulBuffInstance.h"
#include "rpgmodule/buff/C_ConstantSoulBuffInstance.h"
#include "rpgmodule/buff/C_TimedSoulBuffInstance.h"
#include "rpgmodule/buff/C_BuffManager.h"
#include "framework/HashPrimitives.h"
#include "framework/S_TypeFactoryEntry.h"
#include "rpgmodule/buff/C_BuffFactory.h"
#include "rpgmodule/buff/C_BuffInitParamsDefault.h"
#include "rpgmodule/buff/C_InjuredBuffInitParams.h"
#include "rpgmodule/buff/C_SleepBuffInitParams.h"
#include "rpgmodule/buff/C_MoraleContextBuffInitParams.h"
#include "rpgmodule/buff/C_ItemHealthCheckingBuffInitParams.h"
#include "xgenaimodule/C_AIObject.h"
#include "xgenaimodule/C_LinkableObject.h"
#include "xgenaimodule/C_MessageCapableObject.h"
#include "xgenaimodule/C_IntelligentObject.h"
#include "xgenaimodule/C_LinkablesManager.h"
#include "xgenaimodule/C_IntelligentObjectManager.h"
#include "xgenaimodule/EntityToAIMap.h"
#include "xgenaimodule/C_AIPuppet.h"
#include "xgenaimodule/S_InformationRecord.h"
#include "xgenaimodule/C_InformationManager.h"
#include "xgenaimodule/S_InformationResolution.h"
#include "rpgmodule/E_CrimeIconLevel.h"
#include "rpgmodule/I_Location.h"
#include "rpgmodule/C_RPGLocation.h"
#include "rpgmodule/I_RPGLocationManager.h"
#include "rpgmodule/C_RPGLocationManager.h"
#include "rpgmodule/buff/C_TwoStateSoulBuffInstance.h"
#include "rpgmodule/buff/C_WantedBuff.h"
#include "rpgmodule/E_ReputationChangeTarget.h"
#include "rpgmodule/S_AngrinessContribution.h"
#include "rpgmodule/S_TimedFactionEvent.h"
#include "rpgmodule/S_ReputationChangeEntry.h"
#include "rpgmodule/S_ReputationChangeDBData.h"
#include "rpgmodule/S_FactionDef.h"
#include "rpgmodule/C_Faction.h"

// ---- RTTI / kcd_cast smoke test ----
#include "Offsets/RTTI.h"
namespace {
    [[maybe_unused]] void rtti_smoke_test() {
        wh::framework::I_Action* base = nullptr;
        // downcast across the inheritance chain using the game's own RTTI
        auto* hit  = kcd_cast<wh::combatmodule::C_CombatActorActionSyncHit*>(base);
        auto* atk  = kcd_cast<wh::combatmodule::C_CombatActorActionSyncAttack*>(base);
        // sibling/unrelated cast must also compile (returns nullptr at runtime)
        wh::combatmodule::C_CombatActor* actor = nullptr;
        auto* soul = kcd_cast<wh::rpgmodule::C_Soul*>(actor);
        (void)hit; (void)atk; (void)soul;
    }
}
